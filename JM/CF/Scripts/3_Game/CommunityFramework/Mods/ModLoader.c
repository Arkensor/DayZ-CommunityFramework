modded class ModLoader
{
	private static ref map<string, ModStructure> m_ModMap = new map<string, ModStructure>();

	private static ref array<ref ModStructure> m_CF_ModStorage_Mods;
	private static ref map<string, ModStructure> m_CF_ModStorage_ModMap = new map<string, ModStructure>();
	private static ref map<string, ref CF_ModHash> m_CF_ModNameHashMap = new map<string, ref CF_ModHash>();
	private static ref map<string, string> m_CF_ModHashNameMap = new map<string, string>();

	static ref ModStructure Get(string name)
	{
		return Get(GetHash(name));
	}

	static ref ModStructure Get(CF_ModHash hash)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Get(hash.GetPacked());
	}

	static CF_ModHash GetHash(string name)
	{
		if (!m_Loaded) LoadMods();
		CF_ModHash hash = m_CF_ModNameHashMap.Get(name);
		if (!hash)
		{
			hash = new CF_ModHash(name);
			if (m_ModMap.Contains(hash.GetPacked()))
			{
				//! Uh-oh, a collision. Bail by returning NULL.
				return NULL;
			}
			m_CF_ModNameHashMap.Insert(name, hash);
			m_CF_ModHashNameMap.Insert(hash.GetPacked(), name);
		}
		return hash;
	}

	static string GetName(CF_ModHash hash)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModHashNameMap.Get(hash.GetPacked());
	}

	static bool Contains(string name)
	{
		return Contains(GetHash(name));
	}

	static bool Contains(CF_ModHash hash)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Contains(hash.GetPacked());
	}

	static bool Find(string name, out ModStructure mod)
	{
		return Find(GetHash(name), mod);
	}

	static bool Find(CF_ModHash hash, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_ModMap.Find(hash.GetPacked(), mod);
	}

	static bool Find_ModStorage_Mod(string name, out ModStructure mod)
	{
		return Find_ModStorage_Mod(GetHash(name), mod);
	}

	static bool Find_ModStorage_Mod(CF_ModHash hash, out ModStructure mod)
	{
		if (!m_Loaded) LoadMods();
		return m_CF_ModStorage_ModMap.Find(hash.GetPacked(), mod);
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

			CF_ModHash hash = mod.GetHash();

			if (m_ModMap.Contains(hash.GetPacked()))
			{
				Print("WARNING: Ignoring " + mod_name + " (hash " + hash.Repr() +  ") since its hash collides with " + m_ModMap.Get(hash.GetPacked()));
				continue;
			}

			m_ModMap.Insert(hash.GetPacked(), mod);

			m_CF_ModNameHashMap.Insert(mod_name, hash);
			m_CF_ModHashNameMap.Insert(hash.GetPacked(), mod_name);

			//! Enable loading of v3 hash
			CF_ModHash hash_v3 = new CF_ModHash(mod_name, false);
			m_ModMap.Insert(hash_v3.GetPacked(), mod);
			m_CF_ModHashNameMap.Insert(hash_v3.GetPacked(), mod_name);

			if (!GetGame().ConfigIsExisting("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " (hash " + hash.Repr() +  ") for CF_ModStorage");
				continue;
			}

			if (!GetGame().ConfigGetInt("CfgMods " + mod_name + " CF_ModStorage"))
			{
				Print("Ignoring " + mod_name + " (hash " + hash.Repr() +  ") for CF_ModStorage");
				continue;
			}

			Print("Adding " + mod_name + " (hash " + hash.Repr() +  ") for CF_ModStorage");

			m_CF_ModStorage_Mods.Insert(mod);

			m_CF_ModStorage_ModMap.Insert(hash.GetPacked(), mod);

			//! Enable loading of v3 hash
			m_CF_ModStorage_ModMap.Insert(hash_v3.GetPacked(), mod);
		}

		//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DebugPrint, 10000, false);

		m_Loaded = true;
	}

	static void DebugPrint()
	{
		DebugPrint2("CF_ModStorage", m_CF_ModStorage_ModMap);

		DebugPrint2("All", m_ModMap);

		Print("Mod name -> hash key (for lookup only): " + m_CF_ModNameHashMap.Count());
		foreach (string mod_name_key, CF_ModHash hash: m_CF_ModNameHashMap)
		{
			Print(mod_name_key + " " + hash.Repr());
		}

		Print("Mod hash key (for lookup only) -> mod name: " + m_CF_ModHashNameMap.Count());
		foreach (string hash_key, string mod_name: m_CF_ModHashNameMap)
		{
			Print("{" + hash_key + "} -> " + mod_name);
		}
	}

	static void DebugPrint2(string name, ref map<string, ModStructure> modMap)
	{
		Print(name + " mods, hash key (for lookup only) -> mod name -> mod actual hash: " + modMap.Count());
		foreach (string hash_key, ModStructure mod: modMap)
		{
			Print("{" + hash_key + "} -> " + mod.GetName() + " -> " + mod.GetHash().Repr());
		}
	}
};