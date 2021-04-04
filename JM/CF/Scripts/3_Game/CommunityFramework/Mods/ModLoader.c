modded class ModLoader
{
	private static ref map<string, ModStructure> m_ModMap = new map<string, ModStructure>();

	static ref ModStructure Get(string name)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap[name];
	}

	static bool Find(string name, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Find(name, mod);
	}

	override static array<ref ModStructure> GetMods()
	{
		if (!m_Loaded) LoadMods();
		return m_Mods;
	}

	override static void LoadMods()
	{
		m_Mods = new array<ref ModStructure>;

		int mod_count = GetGame().ConfigGetChildrenCount("CfgMods");

		for (int i = 2; i < mod_count; i++)
		{
			string mod_name;
			GetGame().ConfigGetChildName("CfgMods", i, mod_name);

			ref ModStructure mod = new ModStructure(i, "CfgMods " + mod_name);

			m_Mods.Insert(mod);

			m_ModMap.Insert(mod_name, mod);
		}

		m_Loaded = true;
	}
};