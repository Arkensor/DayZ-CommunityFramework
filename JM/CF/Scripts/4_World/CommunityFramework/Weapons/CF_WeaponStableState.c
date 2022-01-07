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
};
