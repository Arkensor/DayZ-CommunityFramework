# Timers

## Instance Timers

Memory management is handled all for you. To create a timer you run `CF_Timer.Create` with the arguments you specify. Note that an interval of `0.0` means the timer will tick every frame.

```csharp
class TestClass : Managed
{	
    void TestClass()
    {
		Widget widget = ...
		float timeToFade = ...
        CF_Timer.Create(this, "FadeIn", 0.0, new CF_TimerParam1<Widget, float>(widget, timeToFade));
    }

    void TimerFunction(CF_Timer timer, float deltaTime, Widget widget, float timeToFade)
    {
        if (timer.GetTimeElapsed() > timeToFade * 1000.0)
        {
            timer.Stop();
            return;
        }

		float alpha = timer.GetTimeElapsed() / (1000.0 * timeToFade);
        widget.SetAlpha(Easing.EaseInCubic(alpha));
    }
};
```

## Generic Timers

You have made the above timer, but then you realised you want to use the timer in more than one spot. Make a new class and inherit it from `CF_TimerBase`. Like with instance timers, these timers have the memory handled for you. Just run `new FadeIn(widget, timeToFade);` and you are good to go.

```csharp
class FadeIn : CF_TimerBase
{
	Widget m_Widget;
	float m_TimeToFade;

    void FadeIn(Widget widget, float timeToFade)
    {
		m_Widget = widget;
		m_TimeToFade = timeToFade;

		SetInterval(0.0);
    }

    override void OnTick(float dt)
    {
        if (timer.GetTimeElapsed() > m_TimeToFade)
        {
            timer.Stop();
            return;
        }

		float alpha = timer.GetTimeElapsed() / (1000.0 * m_TimeToFade);
        m_Widget.SetAlpha(Easing.EaseInCubic(alpha));
    }

	override void OnStart()
	{
		m_Widget.SetAlpha(0);
	}

	override void OnStop()
	{
		m_Widget.SetAlpha(1);
	}
};
```