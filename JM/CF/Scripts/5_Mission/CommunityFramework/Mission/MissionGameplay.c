modded class MissionGameplay
{
	protected bool m_bLoaded;

	void MissionGameplay()
	{
		m_bLoaded = false;
	}

	void ~MissionGameplay()
	{
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		CF_Module_Manager.OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_Module_Manager.OnMissionFinish();
	}

	void OnMissionLoaded()
	{
		CF_Module_Manager.OnMissionLoaded();
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );
	}	
}
