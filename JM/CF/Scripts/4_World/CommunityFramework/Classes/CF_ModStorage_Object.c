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
		
		// 'OnStoreLoad' and 'OnStoreSave' both reset the stream after their operation, we can assume it has been interacted with since

		m_Entity.CF_OnStoreSave(ModLoader.s_CF_ModMap);

		foreach (auto mod : ModLoader.s_CF_Mods)
		{
			mod._WriteHeader();

			// also resets the stream for next 'OnStoreSave'
			mod._CopyStreamTo(stream);
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
			int modVersion = reader.ReadInt();

			// size + string length (+1) + mod version 
			int lengthCopy = size - (modName.Length() + 1) - 1;

			if (ModLoader._CF_UpdateModStorage(modName, modVersion, stream, lengthCopy))
			{
				// Mod is loaded, we have copied the stream to the storage
				continue;
			}

			// Adding data to unloaded list
			stream.SetCurrent(position);
			stream.CopyCurrentTo(m_UnloadedMods, size);
		}

		m_Entity.CF_OnStoreLoad(ModLoader.s_CF_ModMap);

		// Reset the stream for 'OnStoreSave'
		foreach (auto mod : ModLoader.s_CF_Mods)
		{
			mod._ResetStream();
		}

		return true;
	}
};
