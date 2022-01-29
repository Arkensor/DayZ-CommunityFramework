class CF_WeaponStableState : WeaponStableState
{
	bool m_CF_HasBullet;
	bool m_CF_HasMagazine;
	bool m_CF_IsJammed;

	override bool IsRepairEnabled()
	{
		return true;
	}

	override bool HasBullet()
	{
		return m_CF_HasBullet;
	}

	override bool HasMagazine()
	{
		return m_CF_HasMagazine;
	}

	override bool IsJammed()
	{
		return m_CF_IsJammed;
	}

	/**
	 * @brief Prevents default validation. 'm_muzzleHasBullet' is setup in 'WeaponFSM::CF_FindBestStableState' only.
	 */
#ifndef DAYZ_1_15
	override void ValidateMuzzleArray()
	{
		return;
	}
#endif
};
