# Mod Structure

Following the [Modding Basics](https://community.bistudio.com/wiki/DayZ:Modding_Basics), you need to create a `CfgMods` class entry in a config with the name of your mod. Make note of the name of the mod as this is really important, the following example is 'NameOfMod'.

```csharp
class CfgMods
{
	class NameOfMod
	{
	};
};
```

In script, mod the `ModStructure` class and override `OnLoad` as follows. Replace 'NameOfMod' with the name you noted down earlier. Make sure to call super and return it's value if `modName` does not equal the name of your mod.

Currently `OnLoad` is only used for setting the mods current storage version for [Mod Storage](../ModStorage/index.md) by calling `SetStorageVersion`.

```csharp
modded class ModStructure
{
	override bool OnLoad(CF_String modName)
	{
		if (!modName.Equals("NameOfMod"))
		{
			return super.OnLoad(modName);
		}

		return true;
	}
}
```
