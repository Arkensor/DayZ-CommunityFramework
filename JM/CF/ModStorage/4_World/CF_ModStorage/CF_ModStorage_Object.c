class CF_ModStorage_Object<Class T>
{
	T m_Entity;

	autoptr array<ref CF_ModStorage> m_UnloadedMods = new array<ref CF_ModStorage>();

	void CF_ModStorage_Object(T entity)
	{
		m_Entity = entity;
	}

	void OnStoreSave(ParamsWriteContext ctx)
	{
		if (GetGame().SaveVersion() < 116) return;

		ctx.Write(CF_ModStorage.VERSION);
		
		array<ref ModStructure> mods = ModLoader.Get_ModStorage_Mods();

		int i;
		int count = mods.Count() + m_UnloadedMods.Count();
		ctx.Write(count);

		for (i = 0; i < mods.Count(); i++)
		{
			CF_ModStorage store = new CF_ModStorage(mods[i]);

			// call the respective save function so the data is added to CF_ModStorage
			m_Entity.CF_OnStoreSave(store, mods[i].GetName());

			// save the data to the write context
			store.Save(ctx);
		}
		
		// save the data for the unloaded mods
		for (i = 0; i < m_UnloadedMods.Count(); i++)
		{
			m_UnloadedMods[i].Save(ctx);
		}
	}

	bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		//! Clearing the unloaded mods data
		m_UnloadedMods.Clear();

		//! Persistence version is prior to 1.10
		if (version < 116) return true;

		int cf_version;
		if (!ctx.Read(cf_version)) return false;

		//! CF version is prior to ModStorage implementation
		if (cf_version < 2) return true;

		int count;
		if (!ctx.Read(count)) return false;

		for (int i = 0; i < count; i++)
		{
			CF_ModHash hash;
			if (cf_version >= 3)
			{
				hash = new CF_ModHash();
				if (!hash.Load(ctx, cf_version)) return false;
			}
			else
			{
				string modName;
				if (!ctx.Read(modName)) return false;
				hash = ModLoader.GetHash(modName);
			}

			ModStructure mod;
			bool modExists = ModLoader.Find_ModStorage_Mod(hash, mod);

			CF_ModStorage store = new CF_ModStorage(mod, hash);

			if (!store.Load(ctx, cf_version))
			{
				Error( "Failed reading " + GetDebugName(m_Entity) + " for mod '" + ModLoader.GetName(hash) + "' (hash " + hash.Repr() +  ")!");
				return false;
			}

			// check if the mod exists and the version we are loading is greater than zero. 
			// If both pass, go back to the entity and run the store load with the mod.
			if (modExists && store.GetVersion() > 0 && !m_Entity.CF_OnStoreLoad(store, mod.GetName()))
			{
				Error("Failed loading " + GetDebugName(m_Entity) + " for mod '" + mod.GetName() + "' (hash " + hash.Repr() +  ")!");
				return false;
			}

			// Add to the unloaded mods array so the data is resaved when the entity is saved.
			// This is for when a server owner may want to add back in a mod they removed which
			// may have wanted to keep some data.
			if (!modExists && !ModLoader.Contains(hash)) m_UnloadedMods.Insert(store);
		}

		return true;
	}

	static string GetDebugName(Class cls)
	{
		if (!cls) return "[Object] null";

		Object obj;
		if (Class.CastTo(obj, cls)) return "[Object] " + obj.GetType() + ":" + obj.GetNetworkIDString();

		return "[Class] " + cls;
	}
};