# Utils

## Date

## Localiser

## Logging

## Tracing

Useful for when you have a crash and you just aren't sure where or what is causing it. Add these trace methods everywhere and rely on reference counting and unique variables. Make sure to remove any reference of `CF_Trace` from your code base when does, as can be seen in the output below printing to the `script.log` has a heavy toll on performance.

### Example

```csharp
void FunctionOne()
{
	auto trace = CF_Trace_0("FunctionOne");
	
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

### Output

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
