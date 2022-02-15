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
	static const string m_FileName = "modstorageids.bin";
	protected string m_FilePath;

	protected autoptr map<int, ref map<int, ref map<int, ref map<int, ref Param1<bool>>>>> m_IDs = new map<int, ref map<int, ref map<int, ref map<int, ref Param1<bool>>>>>();
	protected bool m_IsLoaded;

	protected autoptr FileSerializer m_Serializer;

	/**
	 * @brief Checks if the persistent ID is in the map. If they aren't in the map then add and write to the file
	 */
	void AddEntity(int b1, int b2, int b3, int b4)
	{
		Load();

		if (!_AddEntity(b1, b2, b3, b4, false))
		{
			return;
		}

		m_Serializer.Write(b1);
		m_Serializer.Write(b2);
		m_Serializer.Write(b3);
		m_Serializer.Write(b4);
	}

	/**
	 * @brief Checks to see if the persistent ID is loaded
	 */
	bool IsEntity(int b1, int b2, int b3, int b4)
	{
		Load();

		auto map_b1 =  m_IDs[b1];
		if (!map_b1)
		{
			return false;
		}

		auto map_b2 = map_b1[b2];
		if (!map_b2)
		{
			return false;
		}

		auto map_b3 = map_b2[b3];
		if (!map_b3)
		{
			return false;
		}

		auto val_b4 = map_b3[b4];
		if (!val_b4)
		{
			return false;
		}

		return true;
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

		if (FileExist(m_FilePath))
		{
			FileHandle handle = OpenFile(m_FilePath, FileMode.READ);
			if (handle != 0)
			{
				// Reads 4 ints (16 bytes) at a time
				int data[4];
				while (ReadFile(handle, data, 16) > 0)
				{
					_AddEntity(data[0], data[1], data[2], data[3], true);
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
	private bool _AddEntity(int b1, int b2, int b3, int b4, bool loaded)
	{
		auto map_b1 =  m_IDs[b1];
		if (!map_b1)
		{
			map_b1 = new map<int, ref map<int, ref map<int, ref Param1<bool>>>>();
			m_IDs[b1] = map_b1;
		}

		auto map_b2 = map_b1[b2];
		if (!map_b2)
		{
			map_b2 = new map<int, ref map<int, ref Param1<bool>>>();
			map_b1[b2] = map_b2;
		}

		auto map_b3 = map_b2[b3];
		if (!map_b3)
		{
			map_b3 = new map<int, ref Param1<bool>>();
			map_b2[b3] = map_b3;
		}

		auto val_b4 = map_b3[b4];
		if (!val_b4)
		{
			val_b4 = new Param1<bool>(loaded);
			map_b3[b4] = val_b4;

			return true;
		}

		return false;
	}
};
