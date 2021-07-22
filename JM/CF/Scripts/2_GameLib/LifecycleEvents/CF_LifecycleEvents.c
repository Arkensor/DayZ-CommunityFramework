class CF_LifecycleEvents
{
    //!Single static class. Do not create with new or spawn - use CF_LifecycleEvents.<something> for access instead.
    protected void CF_LifecycleEvents();
    protected void ~CF_LifecycleEvents();

    static const ref CF_EventHandler OnGameCreate = new CF_EventHandler();
    static const ref CF_EventHandler OnGameDestroy = new CF_EventHandler();
    static const ref CF_EventHandler OnMissionCreate = new CF_EventHandler();
    static const ref CF_EventHandler OnMissionDestroy = new CF_EventHandler();
};
