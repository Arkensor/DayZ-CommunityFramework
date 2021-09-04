modded class DayZGame
{
	override void DeferredInit()
	{
		//CF_TimerBenchmark.Run(5);

		super.DeferredInit();
	}

	override void OnUpdate(bool doSim, float timeslice)
	{
		super.OnUpdate(doSim, timeslice);
		
		CF_TimerBase._UpdateAll(timeslice);
	}
};
