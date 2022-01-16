# Mod Storage

Read [Mod Structure](../ModStructure/index.md) if you haven't done so already to set up the storage version.

## 

In `3_Game` script module, create the following class.

```csharp
class NameOfMod : ModStructure
{
	override void LoadData()
	{
		super.LoadData();

		SetStorageVersion(2);
	}
};
```

In `4_Game` script module, mod the entity class you wish to store data to.

```csharp
modded class KitBase // extends from ItemBase
{
	int someIntVariable;
	string someStringVariable;

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		//! Always call super at the start.
		super.CF_OnStoreSave(storage);

		auto ctx = storage[NameOfMod];
		// As long as the storage version for the mod is greater than zero, it will exist in the storage map
		
		ctx.Write(GetOrientation());
		ctx.Write(someIntVariable);

		ctx.Write(someStringVariable);
	}

	override bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		if (!super.CF_OnStoreLoad(storage))
		{
			// The hierachy of the item failed to load, no point trying to read our variables
			return false;
		}

		auto ctx = storage[NameOfMod];
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
