# Table Of Contents

- [Weapon_Base](#weapon-base)
  * [CF_SpawnMagazine](#cf-spawnmagazine)
  * [CF_AttachMagazine](#cf-attachmagazine)
- [WeaponFSM](#weaponfsm)
  * [CF_FindBestStableState](#cf-findbeststablestate)

# Weapon_Base

## CF_SpawnMagazine

Spawns a magazine into the weapon as an attachment or into the internal magazine. Calls `CF_AttachMagazine` on the spawned magazine.

```csharp
bool CF_SpawnMagazine(string magazineType, int quantity = -1, float health = 1)
```

### Parameters

`magazineType` The class type of the magazine, must inherit from Magazine_Base  
`quantity` The amount of ammunition in the stack/magazine, -1 for max  
`health` The normalized health value, 0 is ruined, 1 is max health  

### Return

True if the magazine was spawned succesfully 

### Example

```csharp
PlayerBase player;
Class.CastTo(player, GetGame().GetPlayer());

Weapon_Base weapon;
Class.CastTo(weapon, player.GetInventory().CreateInInventory("AKM"));

if (weapon.CF_SpawnMagazine("Mag_AKM_Palm30Rnd"))
{
	Print("Spawned magazine");
}
```

## CF_AttachMagazine

Attaches a magazine to the weapon, fills up the internal magazine and chamber for all muzzle points.

```csharp
bool CF_AttachMagazine(Magazine_Base magazine)
```

### Parameters

`magazine` The magazine to be attached 

### Return

True if operation successful

### Example

```csharp
PlayerBase player;
Class.CastTo(player, GetGame().GetPlayer());

Magazine_Base magazine;
Class.CastTo(magazine, player.GetInventory().CreateInInventory("Mag_AKM_Palm30Rnd"));

Weapon_Base weapon;
Class.CastTo(weapon, player.GetInventory().CreateInInventory("AKM"));

if (weapon.CF_AttachMagazine(magazine))
{
	Print("Attached magazine");
}
```

# WeaponFSM

## CF_FindBestStableState

Finds the best stable state that matches the weapon.

```csharp
bool CF_FindBestStableState()
```

### Parameters

`magazine` The magazine to be attached  

### Return

True if the repair was successful

### Example

```csharp
PlayerBase player;
Class.CastTo(player, GetGame().GetPlayer());

array<EntityAI> items();
player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
foreach (auto item : items)
{
	Weapon_Base weapon;
	if (!Class.CastTo(weapon, item)) continue;

	WeaponFSM fsm = weapon.CF_GetFSM();
	if (!fsm) continue;

	if (!fsm.CF_FindBestStableState()) continue;

	Print("Successfully repair weapon");
}
```
