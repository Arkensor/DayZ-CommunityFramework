modded class DayZGame
{
    void DayZGame()
	{
    }

	override void DeferredInit()
	{
		super.DeferredInit();

		GetRPCManager();
		GetLogger();
	}
}