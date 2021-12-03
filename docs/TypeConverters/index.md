# Type Converters

## Creating

Fill as many of the methods as you can for the class

```csharp
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
};
```

## Registering

```csharp
modded class CF_TypeConverterConstructor
{
	override void Register()
	{
		super.Register();

		Insert(PlayerStatBase, CF_TypeConverterPlayerStatBase);
	}
};
```

## Using

```csharp
// This example ignores that you can just use the 'stat' variable
PlayerStatBase stat = GetGame().GetPlayer().GetStatDiet();

Class variable = stat;
CF_TypeConverter converter = CF_TypeConverter.Create(variable.Type());
converter.Read(variable);
Print(converter.GetFloat());
converter.SetString("0.5");
Print(converter.GetFloat());
```
