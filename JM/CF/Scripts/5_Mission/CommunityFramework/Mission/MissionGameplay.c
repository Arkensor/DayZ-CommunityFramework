modded class MissionGameplay
{
	protected bool m_bLoaded;

	void MissionGameplay()
	{
        CF._MissionInit();

		m_bLoaded = false;
	}

	void ~MissionGameplay()
	{
        CF._MissionCleanup();
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetModuleManager().OnSettingsUpdated();
		GetModuleManager().OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetModuleManager().OnMissionFinish();
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		GetModuleManager().OnMissionLoaded();
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );

		GetModuleManager().OnUpdate( timeslice );
	}	
}
