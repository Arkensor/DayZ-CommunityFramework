# Timers

Why should you use these timers over the countless options avaliable in vanilla? Performance and reliability.

There are three issues with vanilla timers, they are:

- The param function arguments are nulled after the first call
- Timer running and iteration is based soley on function calls and dynamic arrays, these are expensive instructions in Enforce Script. 
- The creation and management of timers can be convuluted. They were designed for UI and delayed calls. 

The timers Community Framework is providing will offer improved performance by removing unneccessary function calls and removing the use dynamic arrays. As testing has shown with [Expression's](../ExpressionVM/index.md) there is a huge performance gain when using dual Linked Lists over even static arrays. 

An interval of `0` seconds means the timer will tick for every frame. 

## Instance Timers

Instance Timers can only be ran in `Managed` classes. This benefit provides safe memory management and allows for timers to be deleted when they are no longer required.

### Basic Example - Managed

Memory management is handled all for you when using `Managed`. To create a timer you run `CF_Timer.Create` with the arguments you specify. 

```csharp
class SomeClass : Managed
{
    void SomeClass()
    {
        // The timer will tick every 0.5 seconds.
        CF_Timer.Create(this, "OnTick", 0.5);
    }

    void OnTick(CF_TimerBase timer, float deltaTime)
    {
        Print("Timer has ran for " + timer.m_TimerElapsed + " seconds.");
    }
};
```

### Basic Example - Unmanaged

Make sure to keep the `CF_Timer` alive when the owning class is not `Managed`. The variable must be marked as `autoptr`.

```csharp
class SomeClass
{
    autoptr CF_Timer m_Timer;

    void SomeClass()
    {
        // The timer will tick every 0.5 seconds.
        m_Timer = CF_Timer.Create(this, "OnTick", 0.5);
    }

    void OnTick(CF_TimerBase timer, float deltaTime)
    {
        Print("Timer has ran for " + timer.m_TimerElapsed + " seconds.");
    }
};
```


### Advanced Example

```csharp
class Menu : UIScriptedMenu
{
    static const float FADE_TIME = 0.5;

    void Menu()
    {
        CF_Timer.Create(this, "FadeIn", 0.0, new CF_TimerParam1<Widget, float>(GetLayoutRoot(), FADE_TIME));
    }

    void FadeIn(CF_TimerBase timer, float deltaTime, Widget widget, float timeToFade)
    {
		float alpha = timer.m_TimeElapsed / timeToFade;
        widget.SetAlpha(Math.Clamp(alpha, 0, 1));

        if (timer.m_TimeElapsed >= timeToFade)
        {
            timer.Stop();
        }
    }
};
```

## Generic Timers

Generic Timers are used in places where you want to use the same code for the timer in multiple places at once, or you want to use the timer outside of a `Managed` class or in a static/global function.

### Basic Example

```csharp
class SomeClass
{
    void SomeClass()
    {
        new SomeTimer(this);
    }
};

class SomeTimer : CF_TimerBase
{
    SomeClass m_SomeClass;

    void SomeTimer(SomeClass someClass)
    {
        m_SomeClass = someClass;

        m_Interval = 0.5;
        
        // Start this timer automatically.
        Start();
    }

    override void OnTick(float dt)
    {
        Print("Timer has ran for " + m_TimerElapsed + " seconds and the owner is " + m_SomeClass + ".");

        if (m_SomeClass == null)
        {
            Destroy();
        }
    }
};
```

### Advanced Example

Comparing to the advanced example from `Instance Timers`, this is how the new code will be created and ran. Notice how the code in the menu has shrunk but the overall lines of code has increased. You would use `Generic Timers` when the logic within the timer would be useful in many classes. For most circumstances an `Instance Timer` would be enough.

```csharp
class Menu : UIScriptedMenu
{
    static const float FADE_TIME = 0.5;

    void Menu()
    {
        new FadeIn(GetLayoutRoot(), FADE_TIME);
    }
};

class FadeIn : CF_TimerBase
{
	Widget m_Widget;
	float m_TimeToFade;

    void FadeIn(Widget widget, float timeToFade)
    {
		m_Widget = widget;
		m_TimeToFade = timeToFade;

        // Start this timer automatically
        Start();
    }

    override void OnTick(float dt)
    {
        if (!m_Widget)
        {
            Destroy();
            return;
        }

		float alpha = m_TimeElapsed / m_TimeToFade;
        m_Widget.SetAlpha(Math.Clamp(alpha, 0, 1));

        if (m_TimeElapsed >= m_TimeToFade)
        {
            // If this class instance is not referenced anywhere, then 'Stop' will destroy this class.
            Stop();
        }
    }
};
```
