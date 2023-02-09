modded class MissionBase
{
    void MissionBase()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

        CF_LifecycleEvents.OnMissionCreate.Invoke(this, CF_EventArgs.Empty);
    }

    void ~MissionBase()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

        CF_LifecycleEvents.OnMissionDestroy.Invoke(this, CF_EventArgs.Empty);
    }
};
