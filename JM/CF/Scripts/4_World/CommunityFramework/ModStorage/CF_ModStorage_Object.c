class CF_ModStorage_Object<Class T> : CF_ModStorage_Base
{
	T m_Entity;

	autoptr array<ref CF_ModStorageStream> m_UnloadedMods;

	void CF_ModStorage_Object(T entity)
	{
		m_Entity = entity;
		m_UnloadedMods = new array<ref CF_ModStorageStream>();

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

		CF_Stream stream = new CF_SerializerWriteStream(ctx);

		// 'OnStoreLoad' and 'OnStoreSave' both reset the stream after their operation, we can assume it has been interacted with since

		m_Entity.CF_OnStoreSave(ModLoader.s_CF_ModStoragestorageMap);

		ctx.Write(ModLoader.s_CF_ModStorages.Count());

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
			unloadedMod.WriteToStream(ctx);
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

		int modsRead;
		int unloadedModsRead;
		while (modsRead < numMods)
		{
			modsRead++;

			CF_ModStorageStream stream;
			if (ModLoader._CF_ReadModStorage(ctx, stream))
			{
				// Mod is loaded, we have copied the stream to the storage
				continue;
			}
			
			m_UnloadedMods[unloadedModsRead] = stream;
			unloadedModsRead++;
		}
		
		m_UnloadedMods.Resize(unloadedModsRead);

		m_Entity.CF_OnStoreLoad(ModLoader.s_CF_ModStoragestorageMap);

		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_ModStorages)
		{
			mod._ResetStream();
		}

		return true;
	}
};
