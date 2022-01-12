# Mod Storage

Read [Mod Structure](../ModStructure/index.md) if you haven't done so already to set up the storage version.

```csharp

```

## 

```csharp

modded class KitBase // extends from ItemBase
{
	int someIntVariable;
	string someStringVariable;

	override void CF_OnStoreSave(map<string, CF_ModStorage> storage)
	{
		//! Always call super at the start.
		super.CF_OnStoreSave(storage);

		auto ctx = storage["JM_CommunityFramework"];
		
		ctx.Write(GetOrientation());
		ctx.Write(someIntVariable);

		//! The version of the mod is set in config 'storageVersion' for 'CfgMods' class

		//! redundant check for checking if the writing version matches since the version is always to equal to 'ModStructure::GetVersion'
		if (ctx.GetVersion() > 1)
		{
			ctx.Write(someStringVariable);
		}
	}

	override bool CF_OnStoreLoad(map<string, CF_ModStorage> storage)
	{
		if (!super.CF_OnStoreLoad(storage))
			return false;

		auto ctx = storage["JM_CommunityFramework"];

		vector orientation;
		if (!ctx.Read(orientation)) return false;
		SetOrientation(orientation);

		if (!ctx.Read(someIntVariable)) return false;

		//! The version of the mod is set in config 'storageVersion' for 'CfgMods' class

		someStringVariable = "Default Value";
		if (ctx.GetVersion() > 1)
		{
			if (!ctx.Read(someStringVariable)) return false;
		}
		
		return true;
	}
}
```
