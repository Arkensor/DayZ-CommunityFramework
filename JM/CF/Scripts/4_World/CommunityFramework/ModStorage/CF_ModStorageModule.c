/**
 * @class CF_ModStorageModule
 * 
 * @brief Does not support unloading CF from the mods. Once loaded it can't be removed
 */
#ifndef CF_MODSTORAGE_MODULE_DISABLE
[CF_RegisterModule(CF_ModStorageModule)]
#endif
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
	 * @brief Checks if the item has a player root and if the player ID is in the map. If they aren't in the map then add and write to the file
	 */
	void AddEntity(EntityAI entity)
	{
		Load();

		PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		if (!player || !player.CF_GetQueuedIdentityId() || !_AddPlayer(player.CF_GetQueuedIdentityId(), false))
		{
			return;
		}

		m_Serializer.Write(player.CF_GetQueuedIdentityId());
	}

	/**
	 * @brief Checks to see if the item has a player root and if the player ID is in the map
	 */
	bool IsEntity(EntityAI entity)
	{
		Load();

		PlayerBase player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		if (!player || !player.CF_GetQueuedIdentityId())
		{
			return m_FileExist;
		}

		return m_IDs[player.CF_GetQueuedIdentityId()] != null;
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
