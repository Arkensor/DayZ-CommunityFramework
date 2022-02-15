#ifdef CF_MODSTORAGE_DISABLE
class CF_ModStorageObject<Class T> : CF_ModStorageBase
{
	T m_Entity;

	void CF_ModStorageObject(T entity)
	{
		m_Entity = entity;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
#ifdef CF_MODSTORAGE_TRACE
		auto trace = CF_Trace_1(this, "OnStoreSave").Add(ctx);
#endif

		if (GetGame().SaveVersion() < CF_ModStorage.GAME_VERSION_FIRST_INSTALL)
		{
			return;
		}

        ctx.Write(1);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
#ifdef CF_MODSTORAGE_TRACE
		auto trace = CF_Trace_2(this, "OnStoreLoad").Add(ctx).Add(version);
#endif

		// If the persistence file is before 1.10, cf data doesn't exist
		if (GetGame().SaveVersion() < CF_ModStorage.GAME_VERSION_FIRST_INSTALL)
		{
			return;
		}

        int cf_version;
        if (!ctx.Read(cf_version))
		{
			return false;
		}

		return true;
	}
};
#endif
