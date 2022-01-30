/**
 * @class CF_ModStorageModule
 * 
 * @brief Does not support unloading CF from the mods. Once loaded it can't be removed
 */
[CF_RegisterModule(CF_ModStorageModule)]
class CF_ModStorageModule : CF_ModuleGame
{
	static const string FILEPATH = "$mission:cf_modstoragemodule.txt";

	autoptr map<int, ref map<int, ref map<int, ref map<int, ref Param1<bool>>>>> m_IDs = new map<int, ref map<int, ref map<int, ref map<int, ref Param1<bool>>>>>();
	bool m_IsLoaded;

	ref CF_FileStream m_Stream;
	ref CF_TextWriter m_Writer;

	void AddEntity(int b1, int b2, int b3, int b4)
	{
		Load();

		if (!_AddEntity(b1, b2, b3, b4, false))
		{
			return;
		}

		m_Writer.WriteInt(b1);
		m_Writer.WriteInt(b2);
		m_Writer.WriteInt(b3);
		m_Writer.WriteInt(b4);

		m_Writer.WriteChar("\n");

		m_Stream.Flush();
	}

	/**
	 * @brief Not used.
	 */
	void RemoveEntity(int b1, int b2, int b3, int b4)
	{

	}

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

		auto val_b4 = map_b3[b4] 
		if (!val_b4)
		{
			return false;
		}

		return true;
	}

	void Load(bool reload = false)
	{
		if (m_IsLoaded && !reload)
		{
			return;
		}

		m_IsLoaded = true;

		CF_FileStream stream(FILEPATH, FileMode.READ);
		CF_TextReader reader(stream);

		while (reader.EOF())
		{
			_AddEntity(reader.ReadInt(), reader.ReadInt(), reader.ReadInt(), reader.ReadInt(), true);
		}

		reader.Close();

		m_Stream = new CF_FileStream(FILEPATH, FileMode.APPEND);
		m_Writer = new CF_TextWriter(m_Stream);
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

		auto val_b4 = map_b3[b4] 
		if (!val_b4)
		{
			val_b4 = new Param1<bool>(loaded);
			map_b3[b4] = val_b4;

			return true;
		}

		return false;
	}
};
