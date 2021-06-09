modded class ModLoader
{
	private static ref map<int, ModStructure> m_ModMap = new map<int, ModStructure>();

	private static ref array<ref ModStructure> m_CF_ModStorage_Mods;
	private static ref map<int, ModStructure> m_CF_ModStorage_ModMap = new map<int, ModStructure>();
	private static ref map<string, int> m_CF_ModNameHashMap = new map<string, int>();
	private static ref map<int, string> m_CF_ModHashNameMap = new map<int, string>();

	static ref ModStructure Get(string name)
	{
		return Get(GetHash(name));
	}

	static ref ModStructure Get(int hash)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Get(hash);
	}

	static int GetHash(string name)
	{
		if (!m_Loaded) LoadMods();
		int hash = m_CF_ModNameHashMap.Get(name);
		if (!hash)
		{
			hash = name.Hash();
			if (m_ModMap.Contains(hash))
			{
				//! Uh-oh, a collision. Bail by returning zero.
				return 0;
			}
			m_CF_ModNameHashMap.Insert(name, hash);
			m_CF_ModHashNameMap.Insert(hash, name);
		}
		return hash;
	}

	static string GetName(int hash)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModHashNameMap.Get(hash);
	}

	static bool Contains(string name)
	{
		return Contains(GetHash(name));
	}

	static bool Contains(int hash)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Contains(hash);
	}

	static bool Find(string name, out ModStructure mod)
	{
		return Find(GetHash(name), mod);
	}

	static bool Find(int hash, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Find(hash, mod);
	}

	static bool Find_ModStorage_Mod(string name, out ModStructure mod)
	{
		return Find_ModStorage_Mod(GetHash(name), mod);
	}

	static bool Find_ModStorage_Mod(int hash, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModStorage_ModMap.Find(hash, mod);
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

			int hash = mod.GetHash();

			if (m_ModMap.Contains(hash))
			{
				Print("WARNING: Ignoring " + mod_name + " (hash " + hash + ") since its hash collides with " + m_ModMap.Get(hash));
				continue;
			}

			m_ModMap.Insert(hash, mod);

			m_CF_ModNameHashMap.Insert(mod_name, hash);
			m_CF_ModHashNameMap.Insert(hash, mod_name);

			if (!GetGame().ConfigIsExisting("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " (hash " + hash + ") for CF_ModStorage");
				continue;
			}

			if (!GetGame().ConfigGetInt("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " (hash " + hash + ") for CF_ModStorage");
				continue;
			}

			Print("Adding " + mod_name + " (hash " + hash + ") for CF_ModStorage");

			m_CF_ModStorage_Mods.Insert(mod);

			m_CF_ModStorage_ModMap.Insert(hash, mod);
		}

		m_Loaded = true;
	}
};