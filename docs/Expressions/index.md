# Expressions
Used to parse mathematical expressions in runtime.

```csharp
auto expr = CF_ExpressionVM.Create("5 * 5", CF_MathExpression);
expr
```

## CF_SQFExpression

## CF_MathExpression

The EventHandler feature is a wrapper around `ScriptInvoker` that mimics the [C# EventHandler concept](https://docs.microsoft.com/en-us/dotnet/api/system.eventhandler-1) by introducing subscriber functions that receive a `sender` object and `args` of a variable type `TEventArgs`.

## CF_EventArgs
The class `CF_EventArgs` transports all additional event data besides the `sender` object and is the base class that all non-primitive types of event `args` should inherit from. The constant `CF_EventArgs.Empty` can be used when sending an event that has no data.
```csharp
class MyCustomEventArgs : CF_EventArgs
{
    int someValue;
    float moreData;
};
```