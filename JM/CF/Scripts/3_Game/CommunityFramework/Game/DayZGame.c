modded class DayZGame
{
    void DayZGame()
	{
    }

	override void DeferredInit()
	{
		GetRPCManager();
		GetLogger();

		super.DeferredInit();
	}
}