modded class AnimalBase
{
	autoptr CF_ModStorage_Base m_CF_ModStorage;

	void AnimalBase()
	{
		m_CF_ModStorage = new CF_ModStorage_Object<AnimalBase>(this);
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
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreSave
	 */
	void CF_OnStoreSave(map<string, CF_ModStorage> storage)
	{
	}

	/**
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreLoad
	 */
	bool CF_OnStoreLoad(map<string, CF_ModStorage> storage)
	{
		return true;
	}
};