# RPC Framework for DayZ SA
This is an RPC framework for DayZ SA which aims to resolve the issue of conflicting RPC type ID's and mods.

## How To Use

This is how you would use it in your mod.

### Define an RPC Function
In a class you would have to define the functions which the RPC will call. There is a seperate function for both the server and the client.
These are defined by 'TestRPCFunction_OnServer' and 'TestRPCFunction_OnClient'.

Within the functions, you would need to define the expected Param data that would be sent.

e.g.

```java
void TestRPCFunction_OnServer( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
{
	Param1< string > data; // The param type you are trying to read.
	if ( !ctx.Read( data ) ) return;

    ...
}

void TestRPCFunction_OnClient( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
{
	Param1< string > data; // The param type you are trying to read.
	if ( !ctx.Read( data ) ) return;
	
    ...
}
```

### Add an RPC Function
To add an RPC function you would add this line to the constructor of a shared client and server mission file.

e.g.

```java
GetRPCManager().AddRPC( TestGame, "TestRPCFunction", true );
```

⋅⋅* For the class variable 'TestGame' you would add the instance of the Class which the function resides.

⋅⋅* For the string variable 'TestRPCFunction' you would add the function name. Note: This is without the '_OnServer' or '_OnClient' appended to the function.

⋅⋅* For the boolean variable 'true' you would add a true or false statement depending on if you want the '_OnServer' version of the function to be called in SP or the '_OnClient'. Default is true.


### Call an RPC Function
To call an RPC function you would call the function `SendRPC`. The first argument would be the function name you wish to call on the server and the second would be the Params. You must use the Param class to define the arguments.

e.g.

```java
GetRPCManager().SendRPC( "TestRPCFunction", new Param1< string >("") );
```

### Example
The example can be found [here](https://github.com/Jacob-Mango/DayZ-RPCFramework/blob/master/RPCFramework/Addons/scripts/5_Mission/TestGame.c).