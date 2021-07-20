modded class MissionBase
{
    void MissionBase()
    {
        CF_LifecycleEvents.OnMissionCreate.Invoke(this, CF_EventArgs.Empty);
    }

    void ~MissionBase()
    {
        CF_LifecycleEvents.OnMissionDestroy.Invoke(this, CF_EventArgs.Empty);
    }
};
