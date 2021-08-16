modded class DayZGame
{
    void DayZGame()
    {
        CF_LifecycleEvents.OnGameCreate.Invoke(this, CF_EventArgs.Empty);
    }

    void ~DayZGame()
    {
        CF_LifecycleEvents.OnGameDestroy.Invoke(this, CF_EventArgs.Empty);
    }
};
