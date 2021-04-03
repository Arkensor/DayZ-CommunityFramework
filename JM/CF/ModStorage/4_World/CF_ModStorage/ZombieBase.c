modded class ZombieBase
{
	autoptr CF_ModStorage_Object<ZombieBase> m_CF_ModStorage;

	void ZombieBase()
	{
		m_CF_ModStorage = new CF_ModStorage_Object<ZombieBase>(this);
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		m_CF_ModStorage.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if ( !super.OnStoreLoad(ctx, version)) return false;

		return m_CF_ModStorage.OnStoreLoad(ctx, version);
	}

	/**
	 * @param storage	Where the data is written to
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreSave
	 */
	void CF_OnStoreSave( CF_ModStorage storage, string modName )
	{

	}

	/**
	 * @param storage	Where the data is read from
	 * @param modName	The name of the mod from CfgMods class to check against
	 * 
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreLoad
	 */
	bool CF_OnStoreLoad( CF_ModStorage storage, string modName )
	{
		return true;
	}
};