/**
 * @class CF_ModStorageModule
 * 
 * @brief Does not support unloading CF from the mods. Once loaded it can't be removed
 */
[CF_RegisterModule(CF_ModStorageModule)]
class CF_ModStorageModule : CF_ModuleWorld
{
	static const string FILENAME = "modstorageplayers";
	protected string m_Folder;
	protected string m_FilePath;
	protected string m_LockFilePath;

	//! We only need to keep track of players, because if FILENAME exists,
	//! we already know that all items that are not in player inventory are OK to load from modstorage
	//! because they have been saved prior (as long as the server ran for a couple minutes at least)
	protected autoptr map<string, ref Param1<bool>> m_IDs = new map<string, ref Param1<bool>>();
	protected bool m_IsLoaded;
	protected bool m_FileExist;

	protected autoptr FileSerializer m_Serializer;
	protected FileHandle m_LockFileHandle;

	/**
	 * @note order of operations during connect/disconnect/respawn for reference
	 * (times measured from start of previous step to start of current where applicable and may vary, differences smaller than 100 ms not included)
	 * 
	 * On connect (new character):
	 * 1) MissionServer::OnClientPrepareEvent
	 * 2) EOnClientPrepare (engine, not exposed in script)
	 * 3) OnIdentityCreated (engine, not exposed in script)
	 * 4) 14 s MissionServer::OnClientNewEvent
	 * 5) PlayerBase::OnSelectPlayer
	 * 6) MissionServer::InvokeOnConnect
	 * 
	 * On connect (existing character):
	 * 1) MissionServer::OnClientPrepareEvent
	 * 2) EOnClientPrepare (engine, not exposed in script)
	 * 3) OnIdentityCreated (engine, not exposed in script)
	 * 4) 15 s PlayerBase::OnStoreLoad -> CF_ModStorageObject::OnStoreLoad -> CF_ModStorageModule::IsEntity (PlayerBase::GetIdentity already available)
	 * 5) ItemBase::OnStoreLoad -> CF_ModStorageObject::OnStoreLoad -> CF_ModStorageModule::IsEntity (for each item on player)
	 * 6) MissionServer::OnClientReadyEvent
	 * 7) PlayerBase::OnSelectPlayer
	 * 8) MissionServer::InvokeOnConnect
	 * 
	 * On respawn:
	 * 1) MissionServer::OnClientPrepareEvent
	 * 2) EOnClientPrepare (engine, not exposed in script)
	 * 3) -- s MissionServer::OnClientNewEvent (time varies based on respawnTime)
	 * 4) PlayerBase::OnSelectPlayer
	 * 5) MissionServer::InvokeOnConnect
	 * 
	 * On logout:
	 * 1) MissionServer::OnClientDisconnectedEvent (calls OnClientLogout for CF modules)
	 * 2) MissionServer::OnEvent LogoutCancelEventTypeID (if player cancels logout countdown, calls OnClientLogoutCancelled for CF modules)
	 * 
	 * On disconnect (if logout countdown runs out or player early disconnects):
	 * 1) MissionServer::PlayerDisconnected (calls OnClientDisconnect for CF modules)
	 * 2) MissionServer::InvokeOnDisconnect (called by PlayerDisconnected, only if player character not yet deleted)
	 * 3) PlayerBase::OnStoreSave -> CF_ModStorageObject::OnStoreSave -> CF_ModStorageModule::AddEntity (only if player character not yet deleted)
	 * 4) ItemBase::OnStoreSave -> CF_ModStorageObject::OnStoreSave -> CF_ModStorageModule::AddEntity (for each item on player)
	 */

	override void OnInit()
	{
		super.OnInit();

		EnableMissionFinish();
	}

	override void OnMissionFinish(Class sender, CF_EventArgs args)
	{
		super.OnMissionFinish(sender, args);

		if (m_Serializer)
		{
			m_Serializer.Close();

			if (m_LockFileHandle)
			{
				CloseFile(m_LockFileHandle);
				DeleteFile(m_LockFilePath);
			}
		}
	}

	/**
	 * @brief Checks if the item has a player root and if the player ID is in the map. If they aren't in the map then add and write to the file
	 */
	void AddEntity(EntityAI entity)
	{
		if (!g_Game.IsDedicatedServer())
			return;

		Load();

		if (!m_FileExist)
		{
			//! Make sure to not set this to true before all other entities have been loaded
			MissionBaseWorld mission;
			if (Class.CastTo(mission, g_Game.GetMission()) && mission.CF_IsLoaded())
				m_FileExist = true;
		}

		PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		if (!player)
			return;

		CF_Log.Debug("[CF] CF_ModStorageModule::AddEntity %1 player %2", "" + entity, "" + player);

		string id = player.CF_GetIdentityId(false);

		CF_Log.Debug("  identity ID '%1'", id);

		if (!id)
			return;

		if (!_AddPlayer(id, false))
		{
			CF_Log.Debug("  already added (OK)");
			return;
		}

		CF_Log.Debug("  added");

		m_Serializer.Write(id);
	}

	/**
	 * @brief Checks to see if the item has a player root and if the player ID is in the map
	 */
	bool IsEntity(EntityAI entity)
	{
		if (!g_Game.IsDedicatedServer())
			return true;

		Load();

		PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		if (!player)
			return m_FileExist;

		CF_Log.Debug("[CF] CF_ModStorageModule::IsEntity %1 player %2", "" + entity, "" + player);

		string id = player.CF_GetIdentityId();

		CF_Log.Debug("  identity ID '%1'", id);

		if (!id)
		{
			CF_Log.Debug("  %1", m_FileExist.ToString());
			return m_FileExist;
		}

		CF_Log.Debug("  %1", "" + m_IDs[id]);

		return m_IDs[id] != null;
	}

	/**
	 * @brief Reads the modstorage file
	 */
	void Load(bool reload = false)
	{
		if (m_IsLoaded && !reload)
		{
			return;
		}
		
		m_IsLoaded = true;

		int instanceId = g_Game.ServerConfigGetInt("instanceId");

		m_Folder = "$mission:storage_" + instanceId + "/";
		if (!FileExist(m_Folder))
		{
			MakeDirectory(m_Folder);
		}

		m_Folder += "communityframework/";
		if (!FileExist(m_Folder))
		{
			MakeDirectory(m_Folder);
		}

		m_FilePath = m_Folder + FILENAME + ".bin";
		m_LockFilePath = m_Folder + FILENAME + ".lock";

		if (!reload)
		{
			if (FileExist(m_LockFilePath))
				CF_Log.Warn("File \"%1\" was not closed. Always shut down the server gracefully to prevent data loss.", m_FilePath);

			m_LockFileHandle = OpenFile(m_LockFilePath, FileMode.WRITE);
			if (!m_LockFileHandle)
				CF_Log.Error("Could not create lockfile \"%1\"!", m_LockFilePath);
		}

		if (m_Serializer)
			m_Serializer.Close();
		else
			m_Serializer = new FileSerializer();

		// Clear existing ids
		m_IDs.Clear();

		m_FileExist = FileExist(m_FilePath);
		if (m_FileExist)
		{
			string backup1 = m_Folder + FILENAME + ".001";
			string backup2 = m_Folder + FILENAME + ".002";

			TStringArray filePaths = {m_FilePath};

			if (FileExist(backup1))
				filePaths.Insert(backup1);

			if (FileExist(backup2))
				filePaths.Insert(backup2);

			int failuresCount;

			foreach (string filePath: filePaths)
			{
				FileHandle handle = OpenFile(filePath, FileMode.READ);
				if (handle)
				{
					int len[1];
					string id;
					while (ReadFile(handle, len, 4) > 0 && ReadFile(handle, id, len[0]) > 0)
					{
						if (id.Length() == len[0])
							_AddPlayer(id, true);
						else
							CF_Log.Error("Invalid player ID \"%1\" in \"%2\"", id, filePath);
					}
					CloseFile(handle);
					CF_Log.Info("Added %1 player IDs from \"%2\"", m_IDs.Count().ToString(), filePath);
					break;
				}
				else
				{
					CF_Log.Error("Failed to open \"" + filePath + "\" for reading!");
					failuresCount++;
				}
			}

			if (failuresCount == filePaths.Count())
			{
				_CriticalError("Failed to open \"" + m_FilePath + "\" for reading!");
			}
			else if (!reload)
			{
				//! Cycle backups

				if (FileExist(backup1))
					CopyFile(backup1, backup2);

				CopyFile(m_FilePath, backup1);
			}
			
			if (!m_Serializer.Open(m_FilePath, FileMode.APPEND))
				_CriticalError("Failed to open \"" + m_FilePath + "\" for appending!");
		}
		else
		{
			if (!m_Serializer.Open(m_FilePath, FileMode.WRITE))
				_CriticalError("Failed to open \"" + m_FilePath + "\" for writing!");
		}
	}

	private void _CriticalError(string message)
	{
		Error("[CRITICAL]\t" + message);
		g_Game.RequestExit(1);
	}

	/**
	 * @param loaded If the entity was added from the file
	 * 
	 * @return True if newly added entity
	 */
	private bool _AddPlayer(string id, bool loaded)
	{
		if (!m_IDs[id])
		{
			m_IDs[id] = new Param1<bool>(loaded);

			return true;
		}

		return false;
	}

	void DumpPlayerIDsToFile()
	{
		if (!m_IsLoaded)
		{
			CF_Log.Error("File not loaded");
			return;
		}

		string filePath = m_Folder + FILENAME + "_dump.bin";

		FileSerializer serializer = new FileSerializer();
		if (serializer.Open(filePath, FileMode.WRITE))
		{
			foreach (string id, Param1<bool> loaded: m_IDs)
			{
				serializer.Write(id);
			}
			serializer.Close();
		}
	}
};
