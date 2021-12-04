# Network Variables

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

	private ref CF_NetworkVariables m_NetworkVariables = new CF_NetworkVariables(this);

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
