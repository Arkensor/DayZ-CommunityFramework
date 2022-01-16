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

If you wish, you can set these variables directly in script. This can be done by creating a class of the same and inherits from `ModStructure`.

```csharp
class NameOfMod : ModStructure
{
	override void LoadData()
	{
		super.LoadData();

		SetStorageVersion(1);
	}
}
```
