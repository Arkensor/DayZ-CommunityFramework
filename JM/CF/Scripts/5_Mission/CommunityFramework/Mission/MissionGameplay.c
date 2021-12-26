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

		CF_ModuleCoreManager.OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_ModuleCoreManager.OnMissionFinish();
	}

	void OnMissionLoaded()
	{
		CF_ModuleCoreManager.OnMissionLoaded();
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
