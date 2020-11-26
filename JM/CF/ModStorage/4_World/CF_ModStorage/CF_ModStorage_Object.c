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
		
		array<ref ModStructure> mods = ModLoader.GetMods();

		int i;
		int count = mods.Count() + m_UnloadedMods.Count();
		ctx.Write(count);

		for (i = 0; i < mods.Count(); i++)
		{
			CF_ModStorage store = new CF_ModStorage(mods[i]);

			m_Entity.CF_OnStoreSave(store, mods[i].GetName());

			store.Save(m_Entity, ctx);
		}
		
		for (i = 0; i < m_UnloadedMods.Count(); i++)
		{
			m_UnloadedMods[i].Save(m_Entity, ctx);
		}
	}

	bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
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
			string modName;
			if (!ctx.Read(modName)) return false;

			ModStructure mod;
			bool modExists = ModLoader.Find(modName, mod);

			CF_ModStorage store = new CF_ModStorage(mod);

			if (!store.Load(m_Entity, ctx, cf_version))
			{
				Error( "Failed reading " + Object.GetDebugName(m_Entity) + " for mod '" + modName + "'!");
				return false;
			}

			if (store.GetMod() && store.GetVersion() > 0 && !m_Entity.CF_OnStoreLoad(store, modName))
			{
				Error("Failed loading " + Object.GetDebugName(m_Entity) + " for mod '" + modName + "'!");
				return false;
			}

			if (!modExists) m_UnloadedMods.Insert(store);
		}

		return true;
	}
};