# Mod Storage

## Setup

Before getting started with ModStorage, you need the `CfgMods` parameters to be configured correctly. Here is where we will be applying the global storage version for your mod. `ModStorage` will only be registered for the mod once it has a storage version greater than zero.

```csharp
class CfgMods
{
	class NameOfYourMod
	{
		type = "mod";
		version = "1.2"; // The actual version of the mod
		storageVersion = 2; // Storage version
	};
};
```

**Warning:** Once you have created your `CfgMods` entry and applied a storage version it will be impossible to rename the entry. Any data written to the `ModStorage` will be lost.

### Advanced Workflow

If you wish, you can set some of the variables directly in script. This can be done by creating a class of the same and it inheriting from `ModStructure`.

```csharp
class NameOfYourMod : ModStructure
{
	override void LoadData()
	{
		super.LoadData();

		SetStorageVersion(1);
	}
}
```

## Accessing your ModStorage Context

To access your context pass in the name of your mod as a string. Always check to see if anything was returned as you could be reading from a mod that wasn't loaded at the time of writing.

```csharp
override bool CF_OnStoreLoad(CF_ModStorageMap storage)
{
	if (!super.CF_OnStoreLoad(storage)) return false;

	auto ctx = storage["NameOfYourMod"];
	if (!ctx) return true;

	return true;
}
```

When using a custom class for `ModStructure`, you can instead pass the class typename as a variable instead of a string. 

```csharp
override bool CF_OnStoreLoad(CF_ModStorageMap storage)
{
	...

	auto ctx = storage[NameOfYourMod];
	if (!ctx) return true;

	...
}
```

## Writing Variables

With the `ctx` variable accessed from the `storage` parameter, you can write variables. Only primitive data types can be written to the modstorage. 

```csharp
modded class KitBase
{
	int someVariable;

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		super.CF_OnStoreSave(storage);

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return;
		
		ctx.Write(someVariable);
	}
}
```

### Writing Arrays

```csharp
modded class KitBase
{
	ref array<int> someArray = new array<int>();

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		super.CF_OnStoreSave(storage);

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return;
		
		int count = someArray.Count();

		ctx.Write(count);
		for (int i = 0; i < count; i++)
		{
			ctx.Write(someArray[i]);
		}
	}
}
```

### Writing Classes

For writing classes it is recommended to create a method within the class that handles writing.

```csharp
class SomeClass
{
	string someVariable;

	void OnStoreSave(CF_ModStorage ctx)
	{
		ctx.Write(someVariable);
	}
};

modded class KitBase
{
	ref SomeClass someInstance = new SomeClass();

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		super.CF_OnStoreSave(storage);

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return;
		
		someInstance.OnStoreSave(ctx);
	}
}
```

## Reading Variables

With the `ctx` variable accessed from the `storage` parameter, you can read variables. Only primitive data types can be read from the modstorage. Make sure to keep backwards compatibility between versions so items from when you first created the mod can be loaded a year later. 

```csharp
modded class KitBase
{
	int someVariable;

	override bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		if (!super.CF_OnStoreLoad(storage)) return false;

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return true;

		if (ctx.GetVersion() >= 1)
		{
			if (!ctx.Read(someIntVariable)) return false;
		}

		return true;
	}
}
```

### Reading Arrays

```csharp
modded class KitBase
{
	ref array<int> someArray = new array<int>();

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		super.CF_OnStoreSave(storage);

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return true;
		
		int count;
		if (!ctx.Read(count)) return false;

		someArray.Resize(count);

		for (int i = 0; i < count; i++)
		{
			int someArrayValue;
			if (!ctx.Read(someArrayValue)) return false;

			someArray[i] = someArrayValue; // equivalant of 'someArray.Set(i, someArrayValue);'
		}

		return true;
	}
}
```

### Reading Classes

For writing classes it is recommended to create a method within the class that handles writing.

```csharp
class SomeClass
{
	string someVariable;

	bool OnStoreLoad(CF_ModStorage ctx)
	{
		if (!ctx.Read(someVariable)) return false;

		return true;
	}
};

modded class KitBase
{
	ref SomeClass someInstance = new SomeClass();

	override bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		if (!super.CF_OnStoreLoad(storage)) return false;

		auto ctx = storage["NameOfYourMod"];
		if (!ctx) return true;
		
		if (!someInstance.OnStoreLoad(ctx)) return false;
		
		return true;
	}
}
```

## Example

```csharp
modded class KitBase // extends from ItemBase
{
	int someIntVariable;
	string someStringVariable;

	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		//! Always call super at the start.
		super.CF_OnStoreSave(storage);

		auto ctx = storage[NameOfYourMod];
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

		auto ctx = storage[NameOfYourMod];
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
