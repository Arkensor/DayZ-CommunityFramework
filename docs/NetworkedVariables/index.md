# Networked Variables

A wrapper for serialization of variables that are to be transmitted over the network stack. 

## Registering Variables

## Handling Change

## Custom Types

Register a [Type Converter](../TypeConverters/index.md) to create a custom variable type that can be synchronized. Make sure to override the `Read(Serializer)` and `Write(Serializer)` methods so only your custom fields are sent, and not the class. Make sure to not set Class types to be synchronized as that will have undefined side effects.

## Example

this just an example for arkensor, actual docs later

```csharp
class DataClass
{
	float m_SomeVariable;
};

class SomeClass
{
	static int RPC_ID = 1000000;

	private ref DataClass m_DataHolder = new DataClass();
	private int m_SomeIntVariable;

	private ref CF_NetworkedVariables m_NetworkVariables = new CF_NetworkedVariables(this);

	void SomeClass()
	{
		GetDayZGame().Event_OnRPC.Insert(OnRPC);

		m_NetworkVariables.Register("m_SomeIntVariable");
		m_NetworkVariables.Register("m_DataHolder.m_SomeVariable");
	}

	void OnVariablesSynchronized()
	{
		Print(m_SomeIntVariable);
		Print(m_DataHolder.m_SomeVariable);
	}

	void SetSynchDirty()
	{
		ScriptRPC rpc = new ScriptRPC();

		rpc.Write(GetModuleName());

		m_NetworkVariables.Write(rpc);

		rpc.Send(null, RPC_ID, true, null);
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (id != RPC_ID) return;

		m_NetworkVariables.Read(ctx);

		OnVariablesSynchronized();
	}
	
	void SetSomeClassFloatVariable(float newFloat)
	{
		m_DataHolder.m_SomeVariable = newFloat;

		SetSynchDirty();
	}
	
	void SetSomeIntVariable(int newNum)
	{
		m_SomeIntVariable = newNum;

		SetSynchDirty();
	}
};
```
