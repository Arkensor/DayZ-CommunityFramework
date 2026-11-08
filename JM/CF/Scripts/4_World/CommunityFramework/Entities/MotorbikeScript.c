#ifndef DAYZ_1_29
//! 1.30+
modded class MotorbikeScript
{
	autoptr CF_ModStorageBase m_CF_ModStorage = new CF_ModStorageObject<MotorbikeScript>(this);

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		m_CF_ModStorage.OnStoreSave(ctx);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}

		//! Since CF wasn't updated when DayZ 1.30 Experimental released, MotorbikeScript storage data does not carry
		//! CF data *at all* if the entity isn't tracked, so we have to return early
		if (!CF_Modules<CF_ModStorageModule>.Get().IsEntity(this))
			return true;

		return m_CF_ModStorage.OnStoreLoad(ctx, version);
	}

	/**
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreSave
	 */
	void CF_OnStoreSave(CF_ModStorageMap storage)
	{
	}

	/**
	 * @brief Refer to CF/ModStorage implementation of ItemBase::CF_OnStoreLoad
	 */
	bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		return true;
	}
};
#endif
