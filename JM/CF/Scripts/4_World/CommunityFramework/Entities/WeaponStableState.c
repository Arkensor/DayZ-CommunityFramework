modded class WeaponStableState
{
	bool CF_Equals(WeaponStableState other)
	{
		if (IsRepairEnabled() != other.IsRepairEnabled())
		{
			return false;
		}

		if (HasBullet() != other.HasBullet())
		{
			return false;
		}
		
		if (HasMagazine() != other.HasMagazine())
		{
			return false;
		}

		if (IsJammed() != other.IsJammed())
		{
			return false;
		}

		int muzzleCount = m_muzzleHasBullet.Count();
		if (muzzleCount != other.m_muzzleHasBullet.Count())
		{
			return false;
		}

		for (int muzzle = 0; muzzle < muzzleCount; muzzle++)
		{
			if (m_muzzleHasBullet[muzzle] != other.m_muzzleHasBullet[muzzle])
			{
				return false;
			}
		}

		return true;
	}
};
