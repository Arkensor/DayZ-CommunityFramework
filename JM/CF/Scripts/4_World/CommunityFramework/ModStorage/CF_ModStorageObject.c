#ifdef CF_MODSTORAGE
class CF_ModStorageObject<Class T> : CF_ModStorageBase
{
	T m_Entity;

	autoptr array<ref CF_ModStorage> m_UnloadedMods;

	CF_ModStorageModule m_Module;

	bool m_HasModStorage;

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

		m_Module = CF_Modules<CF_ModStorageModule>.Get();
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
#ifdef CF_MODSTORAGE_TRACE
		auto trace = CF_Trace_1(this).Add(ctx);
#endif

		if (GetGame().SaveVersion() < CF_ModStorage.GAME_VERSION_FIRST_INSTALL)
		{
			return;
		}


		if (!m_HasModStorage)
		{
			// Add the entity to the file so on next load the game knows that it can read the modstorage for the entity
			m_Module.AddEntity(m_Entity);

			m_HasModStorage = true;
		}

		// Write the CF modstorage version
		ctx.Write(CF_ModStorage.VERSION);

		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			mod._ResetStream();
		}

		m_Entity.CF_OnStoreSave(ModLoader.s_CF_ModStorageMap);

		int modsWithDataCount;
		foreach (auto mod2 : ModLoader.s_CF_ModStorages)
		{
			if (mod2.m_MaxIdx > -1) modsWithDataCount++;
		}

		ctx.Write(modsWithDataCount + m_UnloadedMods.Count());

		if (modsWithDataCount)
		{
			foreach (auto mod3 : ModLoader.s_CF_ModStorages)
			{
				// also resets the stream for next 'OnStoreSave'
				if (mod3.m_MaxIdx > -1) mod3._CopyStreamTo(ctx);
			}
		}

		foreach (auto unloadedMod : m_UnloadedMods)
		{
			// Since mod is unloaded, the stream is not reset
			unloadedMod._CopyStreamTo(ctx);
		}
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
#ifdef CF_MODSTORAGE_TRACE
		auto trace = CF_Trace_2(this).Add(ctx).Add(version);
#endif

		// Clearing the unloaded mods data
		m_UnloadedMods.Clear();

		// Persistence version is prior to 1.10
		if (version < CF_ModStorage.GAME_VERSION_FIRST_INSTALL)
		{
			return true;
		}

		// If the version is less than the wipe file, the entity will be added automatically in 'OnStoreSave'
		if (version >= CF_ModStorage.GAME_VERSION_WIPE_FILE)
		{
			if (!m_Module.IsEntity(m_Entity))
			{
				// Since the entity wasn't found we can assume that CF is freshly loaded
				// Highly unlikely anything else happened that can cause this
				// * A new entity won't take the ID of an old entity if it is in circulation
				// * If this is a new entity, OnStoreSave would've been called at some point before 'OnStoreLoad'
				return true;
			}
		}

		int cf_version;
		if (!ctx.Read(cf_version))
		{
			return false;
		}

		// CF version is prior to ModStorage implementation
		if (cf_version < CF_ModStorage.MODSTORAGE_INITIAL_IMPLEMENTATION)
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
				CF_Log.Error("Failed to read modstorage for entity Type=%1, Position=%2", m_Entity.GetType(), m_Entity.GetPosition().ToString());
				break;
			}
		}
		
		m_UnloadedMods.Resize(unloadedModsRead);

		if (modsRead < numMods)
			return false;

		if (!m_Entity.CF_OnStoreLoad(loadedMods))
			ErrorEx(m_Entity.ToString() + "::CF_OnStoreLoad failed", ErrorExSeverity.WARNING);

		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			mod._ResetStream();
		}

		return true;
	}
};
#endif
