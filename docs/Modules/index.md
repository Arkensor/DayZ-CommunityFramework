# Modules

## Variables

Similiar to what is found in [EntityAI](https://github.com/Thurston00/DayZSAEnfScript/blob/8b13d29719fb597de74057ecd4de80ef69e1dfb5/scripts/3_Game/Entities/EntityAI.c#L1747), modules can contain variables that can be synchronized over the network from the server to every client.

A basic implementation for the modules is below. For more advanced examples checkout [Networked Variables](../NetworkedVariables/index.md).

```csharp
class SomeModule : CF_Module
{
	private float m_ModuleTime;
	private float m_ModuleTimeSynch;

	override void OnInit()
	{
		super.OnInit();

		RegisterNetSyncVariable("m_ModuleTimeSynch");
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		Print("The client module is at " + m_ModuleTime);
		Print("The server module is at " + m_ModuleTimeSynch);
	}

	override void OnUpdate(float timeslice)
	{
		m_ModuleTime += timeslice;

		if (GetGame().IsServer())
		{
			m_ModuleTimeSynch += timeslice;
			SetSynchDirty();
		}
	}
};
```