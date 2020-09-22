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
	
	private ref InputGestureCollection m_ActiveKeys = new InputGestureCollection();
	override void OnKeyPress(int key)
	{
		
		m_ActiveKeys.Insert(key, true);


		RoutedCommandMap RoutedCommands = ScriptViewManager.CurrentScriptView.RoutedCommands;
		foreach (ref InputGestureCollection collection, RoutedUICommand cmd: RoutedCommands) {
			if (collection) {
				foreach (KeyCode key2, bool value: collection) {
					PrintFormat("Gesture %1: %2", key2, value);
				}
			}
		}
		
		foreach (KeyCode key3, bool value2: m_ActiveKeys) {
			PrintFormat("Current %1: %2", key3, value2);
		}
		
		RoutedUICommand routed_command = ScriptViewManager.CurrentScriptView.RoutedCommands.Get(m_ActiveKeys);
		if (routed_command) {
			Print("AA");
			//routed_command.Call();
		}
		
		
		super.OnKeyPress(key);
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		m_ActiveKeys.Remove(key);
		
		
	}
}
