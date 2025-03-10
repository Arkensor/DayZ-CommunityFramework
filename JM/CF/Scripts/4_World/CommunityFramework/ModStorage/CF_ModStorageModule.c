/**
 * @class CF_ModStorageModule
 * 
 * @brief Does not support unloading CF from the mods. Once loaded it can't be removed
 */
[CF_RegisterModule(CF_ModStorageModule)]
class CF_ModStorageModule : CF_ModuleWorld
{
	static const string m_FileName = "modstorageplayers.bin";
	protected string m_FilePath;

	//! We only need to keep track of players, because if m_FileName exists,
	//! we already know that all items that are not in player inventory are OK to load from modstorage
	//! because they have been saved prior (as long as the server ran for a couple minutes at least)
	protected autoptr map<string, ref Param1<bool>> m_IDs = new map<string, ref Param1<bool>>();
	protected bool m_IsLoaded;
	protected bool m_FileExist;

	protected autoptr FileSerializer m_Serializer;

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
	 */

	/**
	 * @brief Checks if the item has a player root and if the player ID is in the map. If they aren't in the map then add and write to the file
	 */
	void AddEntity(EntityAI entity)
	{
		if (!g_Game.IsDedicatedServer())
			return;

		Load();

		PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		if (!player)
			return;

#ifdef DIAG_DEVELOPER
		PrintFormat(GetGame().GetTickTime().ToString() + " [CF_ModStorageModule] AddEntity %1 player %2", entity, player);
#endif

		string id = player.CF_GetIdentityId(false);

#ifdef DIAG_DEVELOPER
		PrintFormat("  identity ID '%1'", id);
#endif

		if (!id)
			return;

		if (!_AddPlayer(id, false))
		{
#ifdef DIAG_DEVELOPER
			PrintFormat("  already added (OK)");
#endif
			return;
		}

#ifdef DIAG_DEVELOPER
		PrintFormat("  added");
#endif

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

#ifdef DIAG_DEVELOPER
		PrintFormat(GetGame().GetTickTime().ToString() + " [CF_ModStorageModule] IsEntity %1 player %2", entity, player);
#endif

		string id = player.CF_GetIdentityId();

#ifdef DIAG_DEVELOPER
		PrintFormat("  identity ID '%1'", id);
#endif

		if (!id)
		{
#ifdef DIAG_DEVELOPER
			PrintFormat("  %1", m_FileExist.ToString());
#endif
			return m_FileExist;
		}

#ifdef DIAG_DEVELOPER
		PrintFormat("  %1", m_IDs[id]);
#endif

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

		string folder = "$mission:storage_" + instanceId + "/";
		if (!FileExist(folder))
		{
			MakeDirectory(folder);
		}

		folder += "communityframework/";
		if (!FileExist(folder))
		{
			MakeDirectory(folder);
		}

		m_FilePath = folder + m_FileName;

		if (m_Serializer) m_Serializer.Close();

		// Clear existing ids
		m_IDs.Clear();

		m_FileExist = FileExist(m_FilePath);
		if (m_FileExist)
		{
			m_Serializer = new FileSerializer();
			m_Serializer.Open(m_FilePath, FileMode.READ);
			string id;
			while (true)
			{
				m_Serializer.Read(id);  // always returns true
				if (!id) break;
				_AddPlayer(id, true);
			}
			m_Serializer.Close();
			
			m_Serializer = new FileSerializer();
			m_Serializer.Open(m_FilePath, FileMode.APPEND);
		}
		else
		{
			m_Serializer = new FileSerializer();
			m_Serializer.Open(m_FilePath, FileMode.WRITE);
		}
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
};
