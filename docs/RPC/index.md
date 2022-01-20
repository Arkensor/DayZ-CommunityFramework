# RPC Framework

The legacy RPC framework.

## AddRPC

Registers an RPC function. Must only call once and only on game startup. 

```csharp
bool AddRPC(string modName, string funcName, Class instance, int singlePlayerExecType = SingleplayerExecutionType.Server)
```

### Parameters

`modName` Unique name for the mod within the game, should match your `CfgMods`.
`funcName` The unique for the function within your mod. The function have the following signature `CallType, ParamsReadContext, PlayerIdentity, Object`.
`instance` The class that owns the function. The class must be a singleton
`singlePlayerExecType` How the function is to be executed when the mod is ran in singleplayer

### Example

```csharp
modded class MissionBase
{
	void MissionBase()
	{
		GetRPCManager().AddRPC("RPCTestMod", "TestRPCFunction", this, SingleplayerExecutionType.Both);
	}

	void TestRPCFunction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
	}
}
```

## SendRPC

```csharp
void SendRPC(string modName, string funcName, ref Param params = NULL, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL)
```

### Parameters

`modName` Name of the mod the function is registered under
`funcName` Name of the function to be called on the recieving end
`params` The variables to be sent
`guaranteed` If the function must be sent
`sendToIdentity` The identity to send the RPC to. If `null` and executed on the server then it is sent to all players. Must be `null` on the client.
`sendToTarget` The object target referenced by the rpc

### Example

```csharp
GetRPCManager().SendRPC("RPCTestMod", "TestRPCFunction", new Param1<string>("Hello, World!")); 
```

## Example

```csharp
modded class MissionBase
{
	void MissionBase()
	{
		GetRPCManager().AddRPC("RPCTestMod", "TestRPCFunction", this, SingleplayerExecutionType.Both);
	}

	void TestRPCFunction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<string> data;
		if (!ctx.Read(data)) return;

		if (type == CallType.Server)
		{
			Print("Function called on server!");
		}
		else
		{
			Print("Function called on client!");
		}
	}

	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (key == KeyCode.KC_K)
		{
			GetRPCManager().SendRPC("RPCTestMod", "TestRPCFunction", new Param1<string>("Hello, World!"));  
		}
	}
}
```