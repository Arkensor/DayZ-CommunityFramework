# Type Converters

Provides a unified way of converting types of values to other types, as well as for accessing values and supporting custom serialzation.

## Using Type Converters

Accessing a type converter retrieves the same instance always. 

```csharp
class SomeClass
{
	string m_ID;

	int GetID()
	{
		auto converter = CF_TypeConverter.Get(string);

		converter.SetString(m_ID);

		return converter.GetInt();
	}

	void SetID(int id)
	{
		auto converter = CF_TypeConverter.Get(string);

		converter.SetInt(id);

		m_ID = converter.GetString();
	}
}
```

The variable name can be used to read and write the data. This is made with script reflection in mind. Just pass in the instance holding the variable and the variable name to the `Read` and `Write` methods. 

```csharp
class SomeClass
{
	string m_ID;

	int GetID()
	{
		auto converter = CF_TypeConverter.Get(string);

		converter.Read(this, "m_ID");

		return converter.GetInt();
	}

	void SetID(int id)
	{
		auto converter = CF_TypeConverter.Get(string);

		converter.SetInt(id);

		converter.Write(this, "m_ID");
	}
}
```

## Custom Type Converters

The following code example shows how to create and register an instance of a type converter. Do not create member variables as the instance of the type converter is a singleton and will be the same instance everytime it is used.

```csharp
[CF_RegisterTypeConverter(CF_TypeConverterPlayerStatBase)]
class CF_TypeConverterPlayerStatBase : CF_TypeConverterClass
{
    // Insert code here.
}
```

A common usage of type converters is to convert an object to a primitive type. The following code shows how `PlayerStatBase` can be setup to convert from floats and string primitive types. 

```csharp
[CF_RegisterTypeConverter(CF_TypeConverterPlayerStatBase)]
class CF_TypeConverterPlayerStatBase : CF_TypeConverterClass
{
	override void SetInt(int value)
	{
		m_Value.SetByFloat(value);
	}
	
	override int GetInt()
	{
		return m_Value.Get();
	}

	override void SetFloat(float value)
	{
		m_Value.SetByFloat(value);
	}
	
	override float GetFloat()
	{
		return m_Value.Get();
	}

	override void SetString(string value)
	{
		m_Value.SetByFloat(value.ToFloat());
	}

	override string GetString()
	{
		return GetFloat().ToString();
	}
}
```

Another common usage is for class instances to be serialized and deserialized. The following code will only serialize and deserialize the float variable associated with `PlayerStatBase`.

```csharp
[CF_RegisterTypeConverter(CF_TypeConverterPlayerStatBase)]
class CF_TypeConverterPlayerStatBase : CF_TypeConverterClass
{
    // Insert above example code here.

	override void Read(Serializer ctx)
	{
		float value;
		ctx.Read(value);
		SetFloat(value);
	}

	override void Write(Serializer ctx)
	{
		ctx.Write(GetFloat());
	}
}
```

To use the newly type converters you just have to get the instance and read back the variable.

Unlike with normal type converters, 'Write' does not need to be called as the custom type converter written does not change the instance, just the variable within the instance.

```csharp
auto converter = CF_TypeConverter.Get(PlayerStatBase);
converter.Read(GetGame().GetPlayer(), "m_StatDiet");

Print(converter.GetFloat()); // will print out the current float variable associated with the player
converter.SetString("0.5");
Print(converter.GetFloat()); // will print out "0.5" as a float
```
