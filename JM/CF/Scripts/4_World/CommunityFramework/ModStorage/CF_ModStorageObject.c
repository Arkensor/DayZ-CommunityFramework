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
			// also resets the stream for next 'OnStoreSave'
			mod._CopyStreamTo(ctx);
		}

		foreach (auto unloadedMod : m_UnloadedMods)
		{
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

		CF_ModStorageMap loadedMods();

		int unloadedModsRead;
		for (int modsRead = 0; modsRead < numMods; modsRead++)
		{
			if (!ModLoader._CF_ReadModStorage(ctx, cf_version, m_UnloadedMods, unloadedModsRead, loadedMods))
			{
				int b1, b2, b3, b4;
				m_Entity.GetPersistentID(b1, b2, b3, b4);

				CF_Log.Error("Failed to read modstorage for entity ID=(%0 %1 %2 %3), Type=%5, Position=%6", b1.ToString(), b2.ToString(), b3.ToString(), b4.ToString(), m_Entity.GetType(), m_Entity.GetPosition().ToString());
				return false;
			}
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
