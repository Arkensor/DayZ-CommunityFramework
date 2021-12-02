# Logging

The following table lists the possible log level values and it's corresponding function. Only information with a level equal to or higher than `CF_Log.Level` will be outputted to the `script.log` file.

| Name      | Level | Function        | Description                                                                                                                                                                                   |
| --------- | -----:| ------------    | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| TRACE     | 0     | CF_Log.Trace    | Logs that contain the most detailed messages. These messages should never be enabled in a production environment.                                                                             |
| DEBUG     | 1     | CF_Log.Debug    | Logs that should primarily contain information useful for debugging.                                                                                                                          |
| INFO      | 2     | CF_Log.Info     | Logs that output information that may be relevant to the user.                                                                                                                                |
| WARNING   | 3     | CF_Log.Warn     | Logs that highlight an abnormal action, but does cause the user to notice anything different.                                                                                                 |
| ERROR     | 4     | CF_Log.Error    | Logs that highlight when the current flow of execution is stopped due to a failure. This should indicate if the current activity has a failure and will not result in the game shutting down. |
| CRITICAL  | 5     | CF_Log.Critical | Logs that describe an unrecoverable event and will most likely lead to the shutdown of the game.                                                                                              |
| NONE      | 6     |                 |                                                                                                                                                                                               |

# Context Tracing

Useful for when you have a crash and you just aren't sure where or what is causing it. Add these trace methods in every method. As a precautionary reminder, all outputs heavily impact performance. It is also recommended to place these trace function calls behind preprocessor defines and disabling them in production to improve performance, preventing filling up players drives and so if you ever need to find a new possible cause for crashing you can enable the define.

## Example

```csharp
void SomeGlobalFunction()
{
	auto trace = CF_Trace_0("SomeGlobalFunction");
	
	SomeClass someClass = new SomeClass();
	someClass.MethodOne(0.5);
}

class SomeClass
{
	ref CF_Trace m_SomeClassTrace = CF_Trace_Instance(this);
	
	void SomeClass()
	{
		auto trace = CF_Trace_0(this, "SomeClass");
	}
	
	void MethodOne(float pDt)
	{
		auto trace = CF_Trace_1(this, "SomeFunction").Add(pDt);

		MethodTwo("This is a test string", GetGame().GetPlayer().GetParent());
	}

	void MethodTwo(string message, IEntity parent)
	{
		auto trace = CF_Trace_2(this, "SomeFunction").Add(message).Add(parent);

		MethodThree();
	}

	void MethodThree()
	{
		auto trace = CF_Trace_0(this, "MethodThree");
	}
}
```

## Output

Please note, due to how enforce script works the function end output will happen before the instance destructor does.

```
SCRIPT       : [TRACE] +::FunctionOne ()
SCRIPT       : [TRACE]  +SomeClass<6ec92cd0> ()
SCRIPT       : [TRACE]   +SomeClass<6ec92cd0>::SomeClass ()
SCRIPT       : [TRACE]   -SomeClass<6ec92cd0>::SomeClass Time: 0.0098ms
SCRIPT       : [TRACE]   +SomeClass<6ec92cd0>::SomeFunction (0.5)
SCRIPT       : [TRACE]    +SomeClass<6ec92cd0>::SomeFunction ("This is a test string", NULL)
SCRIPT       : [TRACE]     +SomeClass<6ec92cd0>::MethodThree ()
SCRIPT       : [TRACE]     -SomeClass<6ec92cd0>::MethodThree Time: 0.0019ms
SCRIPT       : [TRACE]    -SomeClass<6ec92cd0>::SomeFunction Time: 0.3468ms
SCRIPT       : [TRACE]   -SomeClass<6ec92cd0>::SomeFunction Time: 0.7035ms
SCRIPT       : [TRACE]  -::FunctionOne Time: 1.6316ms
SCRIPT       : [TRACE] -SomeClass<6ec92cd0> Time: 1.6046ms
```
