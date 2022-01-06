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

		CF_ModuleCoreManager.OnSettingsChanged(this, new CF_EventArgs);
		CF_ModuleCoreManager.OnMissionStart(this, new CF_EventArgs);
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_ModuleCoreManager.OnMissionFinish(this, new CF_EventArgs);
	}

	void OnMissionLoaded()
	{
		CF_ModuleCoreManager.OnMissionLoaded(this, new CF_EventArgs);
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );

		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
	}	
}
