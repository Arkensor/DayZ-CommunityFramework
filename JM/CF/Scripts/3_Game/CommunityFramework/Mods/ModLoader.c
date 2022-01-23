modded class ModLoader
{
	static ref array<ref ModStructure> s_CF_Mods = new array<ref ModStructure>();
	static ref map<string, ModStructure> s_CF_ModMap = new map<string, ModStructure>();

	static ref array<ref CF_ModStorage> s_CF_ModStorages = new array<ref CF_ModStorage>();
	static ref CF_ModStorageMap s_CF_ModStorageMap = new CF_ModStorageMap();
	static ref map<int, ref map<int, CF_ModStorage>> s_CF_ModStorageHashedMap = new map<int, ref map<int, CF_ModStorage>>();

	static CF_ModStorage CF_GetStorage(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "CF_GetStorage").Add(name);
#endif

		LoadMods();

		return s_CF_ModStorageMap[name];
	}

	static bool CF_IsModStorage(string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("ModLoader", "CF_IsModStorage").Add(name);
#endif

		LoadMods();

		return s_CF_ModStorageMap.Contains(name);
	}

	static bool _CF_ReadModStorage(Serializer ctx, int version, out CF_ModStorage storage)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2("ModLoader", "_CF_ReadModStorage").Add(ctx).Add(version);
#endif

		LoadMods();

		int hashA, hashB;
		if (version > 3)
		{
			ctx.Read(hashA);
			ctx.Read(hashB);
		}
		else
		{
			CF_String modName;
			ctx.Read(modName);

			hashA = modName.Hash();
			hashB = modName.Reverse().Hash();
		}

		int modVersion;
		ctx.Read(modVersion);

		auto hash = s_CF_ModStorageHashedMap[hashA];
		bool exists = false;
		if (hash)
		{
			storage = hash[hashB];
			exists = storage != null;
		}

		if (!exists)
		{
			storage = new CF_ModStorage(null);

			storage.m_HashA = hashA;
			storage.m_HashB = hashB;
		}

		storage.m_Version = modVersion;
		ctx.Read(storage.m_Data);

		return exists;
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
		if (m_Loaded)
		{
			return;
		}

#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("ModLoader", "LoadMods");
#endif

		m_Mods = new array<ref ModStructure>;
		m_Loaded = true;

		int modCount = GetGame().ConfigGetChildrenCount("CfgMods");
		for (int i = 2; i < modCount; i++)
		{
			string name;
			GetGame().ConfigGetChildName("CfgMods", i, name);

			ModStructure mod;

			typename type = name.ToType();
			if (!type.IsInherited(ModStructure))
			{
				type = ModStructure;
			}

			if (Class.CastTo(mod, type.Spawn()))
			{
				mod._CF_Init(i, name, "CfgMods " + name);

				m_Mods.Insert(mod);

				s_CF_Mods.Insert(mod);
				s_CF_ModMap.Insert(name, mod);

				if (mod.HasModStorage())
				{
					CF_ModStorage storage = new CF_ModStorage(mod);
					s_CF_ModStorages.Insert(storage);
					s_CF_ModStorageMap.Insert(mod, storage);

					int hashA = mod.m_CF_HashA;
					int hashB = mod.m_CF_HashB;

					map<int, CF_ModStorage> hashStructures = s_CF_ModStorageHashedMap[hashA];
					if (!hashStructures)
					{
						hashStructures = new map<int, CF_ModStorage>();
						s_CF_ModStorageHashedMap.Insert(hashA, hashStructures);
					}

					if (hashStructures.Contains(hashB))
					{
						CF_Log.Error("Mod exists with duplicate hashes! Name=%0 A=%1 B=%2", mod.GetName(), hashA.ToString(), hashB.ToString());
					}

					hashStructures[hashB] = storage;
				}
			}
		}
	}
};
