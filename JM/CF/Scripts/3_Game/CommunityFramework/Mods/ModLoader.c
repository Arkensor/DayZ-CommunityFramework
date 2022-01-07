modded class ModLoader
{
	private static ref map<string, ModStructure> s_CF_ModMap = new map<string, ModStructure>();

	static ref array<ref CF_ModStorage> s_CF_ModStorages = new array<ref CF_ModStorage>();
	static ref map<string, CF_ModStorage> s_CF_ModStoragestorageMap = new map<string, CF_ModStorage>();

	static CF_ModStorage CF_GetStorage(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "CF_GetStorage").Add(name);
#endif

		LoadMods();

		return s_CF_ModStoragestorageMap[name];
	}

	static bool CF_IsModStorage(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "CF_IsModStorage").Add(name);
#endif

		LoadMods();

		return s_CF_ModStoragestorageMap.Contains(name);
	}

	static bool _CF_ReadModStorage(Serializer ctx, out CF_ModStorageStream stream)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "_CF_ReadModStorage").Add(ctx);
#endif

		LoadMods();

		string modName;
		ctx.Read(modName);

		int modVersion;
		ctx.Read(modVersion);

		CF_ModStorage storage;
		if (s_CF_ModStoragestorageMap.Find(modName, storage))
		{
			stream = storage.GetStream();
		}
		else
		{
			stream = new CF_ModStorageStream(ctx);
		}

		stream.m_Name = modName;
		stream.m_Version = modVersion;
		stream.ReadFromStream(ctx);

		return storage != null;
	}

	static ModStructure Get(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "Get").Add(name);
#endif

		LoadMods();

		return s_CF_ModMap[name];
	}

	static bool Contains(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "Contains").Add(name);
#endif

		LoadMods();

		return s_CF_ModMap.Contains(name);
	}

	static bool Find(string name, out ModStructure mod)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "Find").Add(name);
#endif

		LoadMods();

		return s_CF_ModMap.Find(name, mod);
	}

	override static array<ref ModStructure> GetMods()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("ModLoader", "GetMods");
#endif

		LoadMods();

		return m_Mods;
	}

	override static void LoadMods()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("ModLoader", "LoadMods");
#endif

		if (m_Loaded)
		{
			return;
		}

		m_Mods = new array<ref ModStructure>;

		int mod_count = GetGame().ConfigGetChildrenCount("CfgMods");

		for (int i = 2; i < mod_count; i++)
		{
			string mod_name;
			GetGame().ConfigGetChildName("CfgMods", i, mod_name);

			ModStructure mod = new ModStructure(i, "CfgMods " + mod_name);

			m_Mods.Insert(mod);
			s_CF_ModMap.Insert(mod_name, mod);

			if (mod.HasModStorage())
			{
				CF_ModStorage storage = new CF_ModStorage(mod);
				s_CF_ModStorages.Insert(storage);
				s_CF_ModStoragestorageMap.Insert(mod_name, storage);
			}
		}

		m_Loaded = true;
	}
};
