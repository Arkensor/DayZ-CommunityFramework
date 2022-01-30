modded class Weapon_Base
{
	/**
	 * @brief Spawns a magazine into the weapon as an attachment or into the internal magazine. Calls 'CF_AttachMagazine' on the spawned magazine.
	 * 
	 * @param magazineType The class type of the magazine, must inherit from Magazine_Base
	 * @param quantity The amount of ammunition in the stack/magazine, -1 for max
	 * @param health The normalized health value, 0 is ruined, 1 is max health 
	 * 
	 * @return True if the magazine was spawned succesfully 
	 */
	bool CF_SpawnMagazine(string magazineType, int quantity = -1, float health = 1)
	{
		if (!GetGame().IsKindOf(magazineType, "Magazine_Base"))
		{
			return false;
		}

		InventoryLocation location();

		Magazine_Base magazine;

		bool isMagazine = !GetGame().IsKindOf(magazineType, "Ammunition_Base");
		bool success;

		if (isMagazine)
		{
			location.SetAttachment(this, NULL, InventorySlots.MAGAZINE);
			success = Class.CastTo(magazine, SpawnEntity(magazineType, location, ECE_IN_INVENTORY, RF_DEFAULT));
		}
		else
		{
			InventoryLocation weaponLocation();
			success = GetInventory().GetCurrentInventoryLocation(weaponLocation);
			if (success)
			{
				EntityAI parent = weaponLocation.GetParent();

				if (parent && parent.GetInventory().FindFirstFreeLocationForNewEntity(magazineType, FindInventoryLocationType.CARGO, location))
				{
					success = Class.CastTo(magazine, SpawnEntity(magazineType, location, ECE_IN_INVENTORY, RF_DEFAULT));
				}
				else
				{
					success = Class.CastTo(magazine, GetGame().CreateObjectEx(magazineType, GetWorldPosition(), ECE_PLACE_ON_SURFACE));
				}
			}
		}

		if (!success)
		{
			return false;
		}

		if (quantity != -1)
		{
			magazine.ServerSetAmmoCount(quantity);
		}

		magazine.SetHealth01("", "", health);

		if (CF_AttachMagazine(magazine))
		{
			return false;
		}

		if (quantity == -1 && magazine)
		{
			if (isMagazine)
			{
				// make sure the magazine is full
				magazine.ServerSetAmmoMax();
			}
			else
			{
				// delete overfill
				GetGame().ObjectDelete(magazine);
				magazine = null; // may be delayed
			}
		}

		return true;
	}

	/**
	 * @brief Attaches a magazine to the weapon, fills up the internal magazine and chamber for all muzzle points.
	 * 
	 * @param magazine The magazine to be attached
	 * 
	 * @return True if operation successful
	 */
	bool CF_AttachMagazine(Magazine_Base magazine)
	{
		bool isMagazine = !magazine.IsInherited(Ammunition_Base);

		if (GetGame().IsDedicatedServer())
		{
			// Delete the entities from clients
			GetGame().RemoteObjectDelete(this);
			GetGame().RemoteObjectDelete(magazine);
		}

		// Magazine has to attach into the attachment slot
		if (isMagazine)
		{
			InventoryLocation srcLocation();
			magazine.GetInventory().GetCurrentInventoryLocation(srcLocation);

			InventoryLocation dstLocation();
			dstLocation.SetAttachment(this, magazine, InventorySlots.MAGAZINE);

			// If false, then the magazine is already properly attached to the desired slot
			if (!dstLocation.CompareLocationOnly(srcLocation) && !GameInventory.LocationMoveEntity(srcLocation, dstLocation))
			{
				return false;
			}
		}

		float damage;
		string ammoType;

		int ammoCount = magazine.GetAmmoCount();
		int muzzleCount = GetMuzzleCount();

		for (int muzzle = 0; muzzle < muzzleCount; muzzle++)
		{
			int internalMagazineMax = GetInternalMagazineMaxCartridgeCount(muzzle);
			while (GetInternalMagazineCartridgeCount(muzzle) < internalMagazineMax && ammoCount > 0)
			{
				ammoCount--;
				if (magazine.ServerAcquireCartridge(damage, ammoType))
				{
					PushCartridgeToInternalMagazine(muzzle, damage, ammoType);
				}
			}

			if (ammoCount > 0)
			{
				ammoCount--;

				if (magazine.ServerAcquireCartridge(damage, ammoType))
				{
					PushCartridgeToChamber(muzzle, damage, ammoType);
					ShowBullet(muzzle);
				}
			}
		}

		m_fsm.CF_FindBestStableState();

		if (GetGame().IsDedicatedServer())
		{
			GetGame().RemoteObjectCreate(this);

			// When ammoCount reaches zero the magazine is deleted
			if (magazine)
			{
				GetGame().RemoteObjectCreate(magazine);
			}
		}

		return true;
	}

	WeaponFSM CF_GetFSM()
	{
		return m_fsm;
	}

	void CF_SyncSelectionState(WeaponStableState state)
	{
		int muzzleCount = state.m_muzzleHasBullet.Count();
		for (int muzzle = 0; muzzle < muzzleCount; muzzle++)
		{
			if (state.m_muzzleHasBullet[muzzle] != MuzzleState.E)
			{
				ShowBullet(muzzle);
			}
			else
			{
				HideBullet(muzzle);
			}
		}

		if (state.HasMagazine())
		{
			ShowMagazine();
		}
		else
		{
			HideMagazine();
		}
	}
};
