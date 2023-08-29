class CF_LifecycleEvents
{
    static const autoptr CF_EventHandler OnGameCreate = new CF_EventHandler();
    static const autoptr CF_EventHandler OnGameDestroy = new CF_EventHandler();
    static const autoptr CF_EventHandler OnMissionCreate = new CF_EventHandler();
    static const autoptr CF_EventHandler OnMissionDestroy = new CF_EventHandler();

    //!Single static class. Do not create with new or spawn - use CF_LifecycleEvents.<something> for access instead.
    protected void CF_LifecycleEvents()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_LifecycleEvents");
#endif
    }

    protected void ~CF_LifecycleEvents()
    {
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_LifecycleEvents");
#endif
    }
}
