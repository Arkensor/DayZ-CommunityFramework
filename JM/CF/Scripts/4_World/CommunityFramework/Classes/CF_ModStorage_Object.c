class CF_ModStorage_Object<Class T> : CF_ModStorage_Base
{
	T m_Entity;

	ref CF_Stream m_UnloadedMods = new CF_Stream();

	void CF_ModStorage_Object(T entity)
	{
		m_Entity = entity;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		if (GetGame().SaveVersion() < 116)
		{
			return;
		}

		ctx.Write(CF_ModStorage.VERSION);

		CF_Stream stream = new CF_SerializerWriteStream(ctx);

		array<ref ModStructure> mods = ModLoader.Get_ModStorage_Mods();
		for (int i = 0; i < mods.Count(); i++)
		{
			CF_Stream tempStream = new CF_Stream();

			CF_ModStorageWriter store = new CF_ModStorageWriter(mods[i], tempStream);

			// call the respective save function so the data is added to CF_ModStorage
			m_Entity.CF_OnStoreSave(store, mods[i].GetName());

			store.WriteHeader();

			tempStream.CopyTo(stream);
		}

		m_UnloadedMods.CopyTo(stream);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		//! Clearing the unloaded mods data
		m_UnloadedMods.Resize(0);

		//! Persistence version is prior to 1.10
		if (version < 116)
		{
			return true;
		}

		int cf_version;
		if (!ctx.Read(cf_version))
		{
			return false;
		}

		//! CF version is prior to ModStorage implementation
		if (cf_version < 2)
		{
			return true;
		}

		CF_Stream stream = new CF_SerializerReadStream(ctx);

		CF_BinaryReader reader = new CF_BinaryReader(stream);

		Param2<CF_PackedByte, int> position;
		while (!reader.EOF())
		{
			stream.GetCurrent(position);

			int size = reader.ReadInt();
			string modName = reader.ReadString();

			ModStructure mod;
			bool modExists = ModLoader.Find_ModStorage_Mod(modName, mod);
			if (!modExists)
			{
				stream.SetCurrent(position);

				stream.CopyCurrentTo(m_UnloadedMods, size);
				continue;
			}

			CF_ModStorageReader store = new CF_ModStorageReader(mod, stream);

			m_Entity.CF_OnStoreLoad(store, modName);
		}

		return true;
	}
};
