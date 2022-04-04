/**
 * @class CF_ModStorageModule
 * 
 * @brief Does not support unloading CF from the mods. Once loaded it can't be removed
 */
#ifndef CF_MODSTORAGE_MODULE_DISABLE
[CF_RegisterModule(CF_ModStorageModule)]
#endif
class CF_ModStorageModule : CF_ModuleGame
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
	 * @brief Checks if the item has a player root and if the player ID is in the map. If they aren't in the map then add and write to the file
	 */
	void AddEntity(EntityAI entity)
	{
		Load();

		Man player = entity.GetHierarchyRootPlayer();
		if (!player || !player.GetIdentity() || !_AddPlayer(player.GetIdentity().GetId(), false))
		{
			return;
		}

		m_Serializer.Write(player.GetIdentity().GetId());
	}

	/**
	 * @brief Checks to see if the item has a player root and if the player ID is in the map
	 */
	bool IsEntity(EntityAI entity)
	{
		Load();

		Man player = entity.GetHierarchyRootPlayer();
		if (!player || !player.GetIdentity())
		{
			return m_FileExist;
		}

		return m_IDs[player.GetIdentity().GetId()] != null;
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
			FileHandle handle = OpenFile(m_FilePath, FileMode.READ);
			if (handle != 0)
			{
				// Reads 48 bytes (character count + ID string length) at a time
				int count[4];
				string data[44];
				while (ReadFile(handle, count, 4) > 0 && ReadFile(handle, data, 44) > 0)
				{
					string id = "";
					for (int i = 0; i < 44; i++)
					{
						id += data[i];
					}
					_AddPlayer(id, true);
				}

				CloseFile(handle);
			}
			
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
			m_IDs[id] = new Param1<int>(loaded);

			return true;
		}

		return false;
	}
};
