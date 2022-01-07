modded class ModLoader
{
	private static ref map<string, ModStructure> m_ModMap = new map<string, ModStructure>();

	static ref array<ref CF_ModStorage> s_CF_Mods = new array<ref CF_ModStorage>();
	static ref map<string, CF_ModStorage> s_CF_ModMap = new map<string, CF_ModStorage>();

	static CF_ModStorage CF_GetStorage(string name)
	{
		if (!m_Loaded) LoadMods();
		return s_CF_ModMap[name];
	}

	static bool CF_IsModStorage(string name)
	{
		if (!m_Loaded) LoadMods();
		return s_CF_ModMap.Contains(name);
	}

	static bool _CF_UpdateModStorage(string name, int version, CF_Stream stream, int size)
	{
		if (!m_Loaded) LoadMods();

		CF_ModStorage storage;
		if (!s_CF_ModMap.Find(name, storage)) return false;

		storage._CopyStreamFrom(stream, size, version);

		return true;
	}

	static ModStructure Get(string name)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap[name];
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

			ModStructure mod = new ModStructure(i, "CfgMods " + mod_name);

			m_Mods.Insert(mod);
			m_ModMap.Insert(mod_name, mod);

			if (mod.HasModStorage())
			{
				CF_ModStorage storage = new CF_ModStorage(mod);
				s_CF_Mods.Insert(storage);
				s_CF_ModMap.Insert(mod_name, storage);
			}
		}

		m_Loaded = true;
	}
};
