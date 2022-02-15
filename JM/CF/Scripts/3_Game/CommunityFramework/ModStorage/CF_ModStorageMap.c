class CF_ModStorageMap
{
	autoptr map<string, CF_ModStorage> m_Map = new map<string, CF_ModStorage>();

	CF_ModStorage Get(string name)
	{
		return m_Map[name];
	}

	CF_ModStorage Get(typename type)
	{
		return m_Map[type.ToString()];
	}

	bool Contains(string name)
	{
		return m_Map.Contains(name);
	}

	bool Find(string name, out CF_ModStorage storage)
	{
		return m_Map.Find(name, storage);
	}

	void Insert(string name, CF_ModStorage storage)
	{
		m_Map.Insert(name, storage);
	}

	void Insert(ModStructure mod, CF_ModStorage storage)
	{
		m_Map.Insert(mod.ClassName(), storage);
	}
};
