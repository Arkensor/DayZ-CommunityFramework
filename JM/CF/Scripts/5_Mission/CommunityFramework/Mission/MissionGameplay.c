modded class MissionGameplay
{
	override void OnMissionStart()
	{
		super.OnMissionStart();

		CF_ModuleCoreManager.OnSettingsChanged(this, CF_EventArgs.Empty);
		CF_ModuleCoreManager.OnMissionStart(this, CF_EventArgs.Empty);
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_ModuleCoreManager.OnMissionFinish(this, CF_EventArgs.Empty);
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		CF_ModuleCoreManager.OnMissionLoaded(this, CF_EventArgs.Empty);
	}

	override void OnUpdate( float timeslice )
	{
		CF_OnUpdate(timeslice);
		
		super.OnUpdate( timeslice );
	}
};
