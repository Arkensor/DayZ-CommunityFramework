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

		GetModuleManager().OnSettingsUpdated();
		GetModuleManager().OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetModuleManager().OnMissionFinish();
	}

	void OnMissionLoaded()
	{
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
	
	private int m_ActiveKeys;
	
	
	override void OnKeyPress(int key)
	{
		m_ActiveKeys |= key;

		RoutedUICommand routed_command = RoutedCommands.Get(m_ActiveKeys);		
		if (routed_command) {
			routed_command.Execute(new RoutedUICommandArgs(this, null));
		}
		
		super.OnKeyPress(key);
	}
	
	override void OnKeyRelease(int key)
	{
		m_ActiveKeys &= ~key;
		super.OnKeyRelease(key);
	}
}
