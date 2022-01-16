# Mod Storage

Read [Mod Structure](../ModStructure/index.md) if you haven't done so already to set up the storage version.

## 

```csharp
modded class ModStructure
{
	static const string NameOfMod = "NameOfMod";
	static const int NameOfMod_StorageVersion = 2;

	override bool CF_OnLoad(CF_String modName)
	{
		if (!CF_String.EqualsIgnoreCase(modName, NameOfMod))
		{
			return super.CF_OnLoad(modName);
		}

		SetStorageVersion(NameOfMod_StorageVersion);

		return true;
	}
};

modded class KitBase // extends from ItemBase
{
	int someIntVariable;
	string someStringVariable;

	override void CF_OnStoreSave(map<string, CF_ModStorage> storage)
	{
		//! Always call super at the start.
		super.CF_OnStoreSave(storage);

		auto ctx = storage[ModStructure.NameOfMod];
		// As long as the storage version for the mod is greater than zero, it will exist in the storage map
		
		ctx.Write(GetOrientation());
		ctx.Write(someIntVariable);

		ctx.Write(someStringVariable);
	}

	override bool CF_OnStoreLoad(map<string, CF_ModStorage> storage)
	{
		if (!super.CF_OnStoreLoad(storage))
		{
			// The hierachy of the item failed to load, no point trying to read our variables
			return false;
		}

		auto ctx = storage[ModStructure.NameOfMod];
		if (!ctx)
		{
			// Our mod did not previously exist on this item so there is nothing to load. 
			// We let the loader know the item was loaded successfully.
			return true;
		}

		vector orientation;
		if (!ctx.Read(orientation))
		{
			// Failed to read the vector
			return false;
		}

		SetOrientation(orientation);

		if (!ctx.Read(someIntVariable))
		{
			// Failed to read the int
			return false;
		}

		//! The version of the mod is set in config 'storageVersion' for 'CfgMods' class

		someStringVariable = "Default Value";
		if (ctx.GetVersion() > 1)
		{
			// We are checking to see the format of the context container by comparing versions

			if (!ctx.Read(someStringVariable))
			{
				// Failed to read the string
				return false;
			}
		}
		
		return true;
	}
}
```
