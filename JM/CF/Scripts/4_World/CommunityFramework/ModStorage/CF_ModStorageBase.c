class CF_ModStorageBase
{
	CF_ModStorageModule m_Module;

	void OnStoreSave(ParamsWriteContext ctx)
	{
	}

	bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		return true;
	}

	bool OnStoreLoad_CF(ParamsReadContext ctx, int cf_version)
	{
		return true;
	}
};
