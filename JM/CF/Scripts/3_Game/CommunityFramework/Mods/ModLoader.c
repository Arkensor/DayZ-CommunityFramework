modded class ModLoader
{
	private static ref map<string, ModStructure> m_ModMap = new map<string, ModStructure>();

	private static ref array<ref ModStructure> m_CF_ModStorage_Mods;
	private static ref map<string, ModStructure> m_CF_ModStorage_ModMap = new map<string, ModStructure>();

	static ModStructure Get(string name)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModStorage_ModMap[name];
	}

	static bool Contains(string name)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Contains(name);
	}

	static bool Find(string name, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Find(name, mod);
	}

	static bool Find_ModStorage_Mod(string name, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModStorage_ModMap.Find(name, mod);
	}

	override static array<ref ModStructure> GetMods()
	{
		if (!m_Loaded) LoadMods();
		return m_Mods;
	}

	static array<ref ModStructure> Get_ModStorage_Mods()
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModStorage_Mods;
	}

	override static void LoadMods()
	{
		m_Mods = new array<ref ModStructure>;
		m_CF_ModStorage_Mods = new array<ref ModStructure>;

		int mod_count = GetGame().ConfigGetChildrenCount("CfgMods");

		for (int i = 2; i < mod_count; i++)
		{
			string mod_name;
			GetGame().ConfigGetChildName("CfgMods", i, mod_name);

			ref ModStructure mod = new ModStructure(i, "CfgMods " + mod_name);

			m_Mods.Insert(mod);

			m_ModMap.Insert(mod_name, mod);

			if (!GetGame().ConfigIsExisting("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " for CF_ModStorage");
				continue;
			}

			if (!GetGame().ConfigGetInt("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " for CF_ModStorage");
				continue;
			}

			Print("Adding " + mod_name + " for CF_ModStorage");

			m_CF_ModStorage_Mods.Insert(mod);

			m_CF_ModStorage_ModMap.Insert(mod_name, mod);
		}

		m_Loaded = true;
	}
};