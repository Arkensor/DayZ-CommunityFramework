class CF_ModStorageObject<Class T> : CF_ModStorageBase
{
	T m_Entity;

	autoptr array<ref CF_ModStorage> m_UnloadedMods;

	void CF_ModStorageObject(T entity)
	{
		m_Entity = entity;
		m_UnloadedMods = new array<ref CF_ModStorage>();

		ModLoader.LoadMods();
		
		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			mod._ResetStream();
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnStoreSave").Add(ctx);
#endif

		if (GetGame().SaveVersion() < 116)
		{
			return;
		}

		ctx.Write(CF_ModStorage.VERSION);

		// 'OnStoreLoad' and 'OnStoreSave' both reset the stream after their operation, we can assume it has been interacted with since

		m_Entity.CF_OnStoreSave(ModLoader.s_CF_ModStorageMap);

		ctx.Write(ModLoader.s_CF_ModStorages.Count() + m_UnloadedMods.Count());

		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			ctx.Write(mod.GetMod().GetName());
			ctx.Write(mod.GetVersion());

			// also resets the stream for next 'OnStoreSave'
			mod._CopyStreamTo(ctx);
		}

		foreach (auto unloadedMod : m_UnloadedMods)
		{
			ctx.Write(unloadedMod.m_Name);
			ctx.Write(unloadedMod.m_Version);

			// Since mod is unloaded, the stream is not reset
			unloadedMod._CopyStreamTo(ctx);
		}
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnStoreLoad").Add(ctx).Add(version);
#endif

		// Clearing the unloaded mods data
		m_UnloadedMods.Clear();

		// Persistence version is prior to 1.10
		if (version < 116)
		{
			return true;
		}

		int cf_version;
		if (!ctx.Read(cf_version))
		{
			return false;
		}

		// CF version is prior to ModStorage implementation
		if (cf_version < 2)
		{
			return true;
		}

		int numMods;
		if (!ctx.Read(numMods))
		{
			return false;
		}

		m_UnloadedMods.Resize(numMods);

		map<string, CF_ModStorage> loadedMods();

		int modsRead;
		int unloadedModsRead;
		while (modsRead < numMods)
		{
			modsRead++;

			CF_ModStorage storage;
			if (ModLoader._CF_ReadModStorage(ctx, storage))
			{
				loadedMods.Insert(storage.m_Name, storage);

				// Mod is loaded, we have copied the stream to the storage
				continue;
			}
			
			m_UnloadedMods[unloadedModsRead] = storage;
			unloadedModsRead++;
		}
		
		m_UnloadedMods.Resize(unloadedModsRead);

		m_Entity.CF_OnStoreLoad(loadedMods);

		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			mod._ResetStream();
		}

		return true;
	}
};
