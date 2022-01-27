# CF_InputBindings

All input bindings are only executed on the client. 

## CF_InputBindings

Constructor. Adds to the list of all input binding managers. Should be called on parent class construction

```csharp
void CF_InputBindings(Class instance)
```

### Parameters

`instance` The input binding parent

### Example

```csharp
class SomeClass
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);
};
```

## Bind

Binds input to head, pushes other entries back

```csharp
void Bind(string callback, string input, bool preventCallInMenu = false)
```

### Parameters

`callback` The function within the input binding parent to call
`input` The name of the input
`preventCallInMenu` If the binding can be called while a menu is open

### Example

```csharp
class SomeClass
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	void SomeClass()
	{
		m_CF_Bindings.Bind("PrintMessage", "UAUIBack", false);
	}

	void PrintMessage(UAInput input)
	{
		Print("Hello, World!");
	}
};
```

## Bind

Binds input to head, pushes other entries back

```csharp
void Bind(string callback, int input, bool preventCallInMenu = false)
```

### Parameters

`callback` The function within the input binding parent to call
`input` The ID of the input. All inputs found within modded inputs is generated as a global int variable of the same name
`preventCallInMenu` If the binding can be called while a menu is open

### Example

```csharp
class SomeClass
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	void SomeClass()
	{
		m_CF_Bindings.Bind("PrintMessage", UAUIBack, false);
	}

	void PrintMessage(UAInput input)
	{
		Print("Hello, World!");
	}
};
```

## Bind

Binds input to head, pushes other entries back

```csharp
void Bind(string callback, UAInput input, bool preventCallInMenu = false)
```

### Parameters

`callback` The function within the input binding parent to call
`input` The instance of the input
`preventCallInMenu` If the binding can be called while a menu is open

### Example

```csharp
class SomeClass
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	void SomeClass()
	{
		m_CF_Bindings.Bind("PrintMessage", GetUApi().GetInputByID(UAUIBack), false);
	}

	void PrintMessage(UAInput input)
	{
		Print("Hello, World!");
	}
};
```

## Bind

Binds input to head, pushes other entries back

```csharp
void Bind(CF_InputBinding binding)
```

### Parameters

`binding` The instance of the binding to add to the list

### Example

```csharp
class SomeClass
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	void SomeClass()
	{
		CF_InputBinding binding = new CF_InputBinding();
		binding.m_Function = "PrintMessage";
		binding.m_Input = GetUApi().GetInputByID(UAUIBack);
		binding.m_LimitMenu = false;

		m_CF_Bindings.Bind(binding);
	}

	void PrintMessage(UAInput input)
	{
		Print("Hello, World!");
	}
};
```
