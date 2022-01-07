class CF_ModStorage_Base
{
	void OnStoreSave(ParamsWriteContext ctx)
	{
	}

	bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		return true;
	}
};
