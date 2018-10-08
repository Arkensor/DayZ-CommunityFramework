# RPC Framework for DayZ SA
This is an RPC framework for DayZ SA which aims to resolve the issue of conflicting RPC type ID's and mods.

This framework allows the use of cross mod RPC calling, better defining of the functions and is less prone to errors with mismatching RPC ID's.

## How To Use

This is how you would use this framework within your mod. 

### Setup

You would want to install the pre-packaged mod found [here](https://github.com/Jacob-Mango/DayZ-RPCFramework/releases) in the releases section.

Unzip the file and drag the folder `RPCFramework` into the root of your game and server directory. It is already signed.

When starting the game and/or server, make sure to add the mod first by using `-mod=RPCFramework;` and then append the rest of your mods afterwards. Seperate using the `;` character.

To use the framework with your mod you would want to add the mod to the config.cpp of your scripts PBO.

e.g.

```cpp
class CfgPatches
{
    class ...
    {
        ...
        requiredAddons[]=
        {
            "RPC_Scripts",
            ...
        };
    };
};
```

### Define an RPC Function
In a class you would have to define the functions which the RPC will call. 

Within the function, you would need to define the expected Param data that would be sent. You would also add a check to define how the function is being called (on server or on client). 

e.g.

```java
void TestRPCFunction( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
{
    Param1< string > data;
    if ( !ctx.Read( data ) ) return;

    if( type == CallType.Server )
    {
        Print( "Server function called!" );
    }
    else
    {
        Print( "Client function called!" );
    }
}
```

### Add an RPC Function
To add an RPC function you would add this line to the constructor of a shared client and server mission file.

e.g.

```java
GetRPCManager().AddRPC( "RPCTestMod", "TestRPCFunction", this, SingeplayerExecutionType.Both ); 
```

* For the string variable 'RPCTestMod' you would add the mod name. This would be a namespace. Try to make this as unique as possible.
* For the class variable 'this' you would add the instance of the Class which the function resides.
* For the string variable 'TestRPCFunction' you would add the function name. 
* For the SingeplayerExecutionType variable 'Both' which would define how you would want the function to be called in SinglePlayer (Offline Mode).

### Call an RPC Function
To call an RPC function you would call the function `SendRPC`. The first argument would be the mod name which you would have defined. The second argument would be the function name you wish to call on the server and the second would be the Params. You must use the Param class to define the arguments.

e.g.

```java
GetRPCManager().SendRPC( "RPCTestMod", "TestRPCFunction", new Param1< string >( "Hello, World!" ) );  
```

### Example
An example can be found [here](https://github.com/Jacob-Mango/DayZ-RPCFramework/blob/master/Examples/RPCFramework_Test/Addons/test/5_Mission/TestGame.c).

## Projects

Here are some projects that are already planned to use this Framework.

* HypeTrain by Arkensor
* DayZBR by Kegan Hollern

## Contributors

* [Jacob_Mango](https://github.com/Jacob-Mango)
* [Arkensor](https://github.com/Arkensor)
* [Kegan Hollern](https://gitlab.desolationredux.com/kegan)