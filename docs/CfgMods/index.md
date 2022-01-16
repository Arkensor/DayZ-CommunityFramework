# Mod Structure

Following the [Modding Basics](https://community.bistudio.com/wiki/DayZ:Modding_Basics), you need to create a `CfgMods` class entry in a config with the name of your mod. Make note of the name of the mod as this is really important. In the following example we uss `NameOfMod`, this can be anything, it just to be unique to you. 

```csharp
class CfgMods
{
	class NameOfMod
	{
		type = "mod";
		dir = "mod/prefix";
		inputs = "mod/prefix/scripts/inputs.xml";
		creditsJson = "mod/prefix/scripts/credits.json";
		version = "1.2"; // The actual version of the mod
		storageVersion = 2; // Storage version
	};
};
```

## Advanced Workflow

If you wish, you can set these variables directly in script. This can be done by modding the `ModStructure` class and overriding `CF_OnLoad`.

```csharp
modded class ModStructure
{
	static const string NameOfMod = "NameOfMod";
	static const int NameOfMod_StorageVersion = 1;

	override bool CF_OnLoad(CF_String modName)
	{
		if (!CF_String.EqualsIgnoreCase(modName, NameOfMod))
		{
			return super.CF_OnLoad(modName);
		}

		SetStorageVersion(NameOfMod_StorageVersion);

		return true;
	}
}
```
