modded class MissionGameplay
{
	void MissionGameplay()
	{
		if (GetGame().IsServer())
		{
			CF_Debug.SetAllowed(true);
		}
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		CF_ModuleCoreManager.OnSettingsChanged(this, new CF_EventArgs);
		CF_ModuleCoreManager.OnMissionStart(this, new CF_EventArgs);
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_ModuleCoreManager.OnMissionFinish(this, new CF_EventArgs);
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		CF_ModuleCoreManager.OnMissionLoaded(this, new CF_EventArgs);
	}

	override void OnUpdate( float timeslice )
	{
		CF_OnUpdate(timeslice);
		
		super.OnUpdate( timeslice );
	}
};
