# Localiser
A localising system for networked messages. 

## Creating and Using

The following example is using strings found in the DayZ stringtable. 

The localiser class has overloaded the array assignment operator to allow setting of the string table keys and placing in other variables at the desired format.

```csharp
CF_Localiser localiser = new CF_Localiser("STR_DATE_FORMAT");
localiser.Add(5);
localiser[1] = "Hello";
localiser[2] = "STR_NOVEMBER";

Print(localiser.Format());
// English: "5, Hello Nov"
```

## Working with RPCs

Currently not supported with RPCManager.

### Sending

```csharp
CF_Localiser localiser = new CF_Localiser("STR_DATE_FORMAT");
localiser[0] = "STR_FRIDAY";
localiser[1] = "STR_DECEMBER";
localiser[2] = 2021;

ScriptRPC rpc = new ScriptRPC();
CF_Localiser.Write(rpc, localiser);
rpc.Send(null, 1024, false, null);
```

### Reading

```csharp
void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
{
	CF_Localiser localiser;
	CF_Localiser.Read(rpc, localiser);
	Print(localiser.Format());
	// English: "Fri, Dec 2021"
}
```
