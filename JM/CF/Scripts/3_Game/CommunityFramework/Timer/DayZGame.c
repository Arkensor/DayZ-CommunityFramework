modded class DayZGame
{
	override void OnUpdate(bool doSim, float timeslice)
	{
		super.OnUpdate(doSim, timeslice);
		
		CF_TimerBase._Update(timeslice);
	}
};
