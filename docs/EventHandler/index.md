# EventHandler
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

## CF_EventHandler
The class `CF_EventHandler` is a substitute for `CF_EventHandlerT<CF_EventArgs>` and will be the correct choice for most use-cases. Please see the `CF_EventHandlerT<TEventArgs>` section for more information.

## CF_EventHandlerT\<TEventArgs>
The class `CF_EventHandlerT<TEventArgs>`must be instantiated to declare a subscribable event. The template argument `TEventArgs` can be used to send a single primitive as event `args` or to restrict what kind of `CF_EventArgs` inherited type is accepted for invoking the event.
```csharp
class CF_EventHandlerT_SetupDemo
{
    static ref CF_EventHandlerT<float> MyStaticPrimtiveArgsEvent = new CF_EventHandlerT<float>();
    
    ref CF_EventHandlerT<MyCustomEventArgs> MyInstanceCustomArgsEvent;   
};
```

### Invoking the event
After having setup an EventHandler instance, you can invoke the event by calling the `Invoke(Class sender = NULL, TEventArgs args = NULL)` method on it.
This will cause all registered subscribers to be executed in the order that they were registered in.
A common value for the sender parameter will be the object instance that called the invoke.
```csharp
class CF_EventHandlerT_InvokeDemo
{
    ref CF_EventHandlerT<CF_EventArgs> MyEvent;
    
    void InvokeEvent()
    {
        MyEvent.Invoke(this, CF_EventArgs.Empty);
        
        //Sender only param alternative - args will be NULL
        MyEvent.Invoke(this);
        
        //No params alternative - sender will be NULL, args will be NULL
        MyEvent.Invoke();
    }
};
```

### Registering subscribers
Functions that shall be executed when the event is invoked can be registered as subscribers by calling the `AddSubscriber(ScriptCaller subscriber)` method on the EventHandler instance.
You can register global and static functions as well as instance methods.
```csharp
void MyGlobalPrimtiveHandler(Class sender, float args) {} //for CF_EventHandlerT<float>

class CF_EventHandlerT_SubscribeDemo
{
    static void MySubscriberStaticFunction(Class sender, MyCustomEventArgs args) {} //for CF_EventHandlerT<MyCustomEventArgs>
    
    void MySubscriberMethod(Class sender, CF_EventArgs args) {} //for CF_EventHandlerT<CF_EventArgs> aka CF_EventHandler
};

void RegisterSubscribersDemo()
{
    //Global function
    new CF_EventHandlerT<float>().AddSubscriber(ScriptCaller.Create(MyGlobalPrimtiveHandler));
    
    //Static function
    new CF_EventHandlerT<MyCustomEventArgs>().AddSubscriber(ScriptCaller.Create(CF_EventHandlerT_SubscribeDemo.MySubscriberStaticFunction));
    
    //Instance method
    auto instance = new CF_EventHandlerT_DemoSubscribe(); //Must be kept alive or the subscriber function will be invalid.
    new CF_EventHandler().AddSubscriber(ScriptCaller.Create(instance.MySubscriberMethod));
}
```
You can also subscribe a single function to multiple EventHandlers that have different `TEventArgs` if you use `CF_EventArgs` as `args` type and do a runtime type check.
```csharp
void HandleCustomArgsAlternative(Class sender, CF_EventArgs args) 
{
    MyCustomEventArgs customArgs;
    if(Class.CastTo(customArgs, args))
    {
        //do stuff here
    }
}
```
Similar to how C# handles it, the subscribing function can omit the `args` or both parameters and still be invokable on the same kind of event.
```csharp
void HandleSomethingVariant1(Class sender) {}
void HandleSomethingVariant2() {}
```
#### Subscriber attributes
If the subscriber function is global or static you may make use of custom attributes as decatorators above the functions itself.
There are two types of attributes: `CF_EventSubscriber` for subscribing up to 9 EventHandler instances and `CF_MultiEventSubscriber` if you need more.
```csharp
//You can have them in one line
[CF_EventSubscriber(ScriptCaller.Create(TestGlobalEventSubscriber), Event1, Event2)] 
void TestGlobalEventSubscriber()
{
    Print("TestGlobalEventSubscriber");
}

class StaticWrapper
{
    //Or across multiple lines.
    //Only the section opening [ and closing ] must be on the same line as the attribute opening ( and closing )
    [CF_MultiEventSubscriber(ScriptCaller.Create(StaticWrapper.TestMultiEventSubscriber), 
    {
        Event1,
        Event2,
        ...
        EventN
    })]
    static void TestMultiEventSubscriber()
    {
        Print("TestMultiEventSubscriber");
    }
}
```
