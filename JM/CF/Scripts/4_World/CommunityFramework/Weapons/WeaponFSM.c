modded class WeaponFSM
{
	/**
	 * @brief Finds the best stable state that matches the weapon.
	 * 
	 * @return True if the repair was successful
	 */
	bool CF_FindBestStableState()
	{
		// Only repair stable states
		WeaponStableState state = WeaponStableState.Cast(m_State);
		if (!state || !state.IsRepairEnabled())
		{
			return false;
		}

		// Make sure a weapon is assigned
		Weapon_Base weapon = state.m_weapon;
		if (!weapon)
		{
			return false;
		}

		CF_WeaponStableState comparingState = new CF_WeaponStableState();
		comparingState.m_muzzleHasBullet.Clear();

		int muzzleCount = weapon.GetMuzzleCount();
		for (int muzzle = 0; muzzle < muzzleCount; muzzle++)
		{
			bool magazine = weapon.GetMagazine(muzzle) != null;
			bool jammed = weapon.IsChamberJammed(muzzle);
			bool empty = weapon.IsChamberEmpty(muzzle);
			bool firedOut = weapon.IsChamberFiredOut(muzzle);
			bool loaded = !empty && !firedOut;

			if (loaded)
			{
				comparingState.m_muzzleHasBullet.Insert(MuzzleState.L);
			}
			else if (empty)
			{
				comparingState.m_muzzleHasBullet.Insert(MuzzleState.E);
			}
			else if (firedOut)
			{
				comparingState.m_muzzleHasBullet.Insert(MuzzleState.F);
			}

			comparingState.m_CF_HasMagazine |= magazine;
			comparingState.m_CF_HasBullet |= !empty;
			comparingState.m_CF_IsJammed |= jammed;
		}

		int count = m_Transitions.Count();
		for (int i = 0; i < count; ++i)
		{
			WeaponStableState srcState;
			if (!Class.CastTo(srcState, m_Transitions[i].m_srcState))
			{
				continue;
			}

			if (!srcState.CF_Equals(comparingState))
			{
				continue;
			}

			Terminate();
			m_State = srcState;
			Start(null, true);
			weapon.CF_SyncSelectionState(srcState);
			srcState.SyncAnimState();

			return true;
		}

		return false;
	}
};
