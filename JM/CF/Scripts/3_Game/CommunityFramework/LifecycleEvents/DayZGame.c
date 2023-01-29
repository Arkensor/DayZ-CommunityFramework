modded class DayZGame
{
    void DayZGame()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

        CF_LifecycleEvents.OnGameCreate.Invoke(this, CF_EventArgs.Empty);
    }

    void ~DayZGame()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

        CF_LifecycleEvents.OnGameDestroy.Invoke(this, CF_EventArgs.Empty);
    }
};
