# Expressions
Used to parse mathematical expressions in runtime. The default format used is `CF_MathExpression`. All values are treated as floating point numbers. Expressions are optimized for evaluating, not compiling. Recommended practise is to compile as few times as needed. 

```csharp
auto expr = CF_ExpressionVM.Compile("5 * 5");
float value = expr.Evaluate();
Print(value); // 25
```

## CF_MathExpression
For performance reasons every parameter after the first one is evaluated at compile time and as such can't contain user defined variables. The first parameter is treated as if it was in brackets following the BODMAS principle.

```csharp
auto expr = CF_ExpressionVM.Compile("4 * factor(4, 0, 5)", CF_MathExpression);
float value = expr.Evaluate();
Print(value); // 4
```

## CF_SQFExpression
PBO config binaries such as SoundShaders use a similar mathematical syntax found in SQF. They make use of square brackets for denoting parameters within a function. For performance reasons, these parameters are evaluated at compile time and as such can't contain user defined variables.

```csharp
auto expr = CF_ExpressionVM.Compile("4 * (4 factor [0, 5])", CF_SQFExpression);
float value = expr.Evaluate();
Print(value); // 4
```

## Functions
Functions and operators are treated the same way. Not all functions require brackets and parameters. In `CF_MathExpression` the first 'parameter' is a continuation of the expression and can have variables. The other parameters are evaluated during compilation so can't have variables. In `CF_SQFExpression` the first 'parameter' is given from context and is decalred before the function call.

### Custom Functions
Custom functions can be registered for use if needed. They are globally added so any expression in any mod can use them. 

```csharp
class ExpressionFunctionPow : CF_ExpressionFunction
{
	[CF_EventSubscriber(ExpressionFunctionPow.Init, CF_LifecycleEvents.OnGameCreate)]
	static void Init()
	{
		CF_ExpressionVM.AddFunction("pow", new ExpressionFunctionPow());
	}

	void ExpressionFunctionPow()
	{
		params = 1;
	}

	override void Call()
	{
		//! minimize variable moving and declarations
		g_CF_Expression_stack[g_CF_Expression_stackPointer] = Math.Pow(g_CF_Expression_stack[g_CF_Expression_stackPointer], g_CF_Expression_instruction.param1);
	}
};
```

The above function would be used like the following in each respective expression type

Expression Type|Input
-|-
`CF_SQFExpression`|`(someVar pow [4])`
`CF_MathExpression`|`pow(someVar, 4)`

## Variables
All expressions can make use of user defined variables that can be re-evaluated during runtime. They are loaded from an array of strings during compile. When evaluating the array of floats for the variables must be the same length as the string array.

```csharp
array<string> variableNames = { "speed" };
array<float> variableValues = { 50.0 };

auto expr = CF_ExpressionVM.Compile("50 * (speed factor [0, 100])", variableNames, CF_MathExpression);
float value = expr.Evaluate(variableValues);
Print(value); // 25
```