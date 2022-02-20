modded class MissionBase
{
	protected bool m_bLoaded = false;

	ref CF_EventUpdateArgs m_CF_EventUpdateArgs = new CF_EventUpdateArgs();
	
	void MissionBase()
	{
		CF_ModuleGameManager.UpdateGameFlag();

		// Deprecated
		if (!ModuleManagerExists())
		{
			CreateModuleManager(new JMModuleConstructor());
		}
	}

	void OnMissionLoaded()
	{
	}

	void CF_OnUpdate(float timeslice)
	{
		if (g_Game.IsLoading())
		{
			return;
		}

		if (!m_bLoaded)
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}

		m_CF_EventUpdateArgs.DeltaTime = timeslice;
		CF_ModuleGameManager.OnUpdate(this, m_CF_EventUpdateArgs);
	}
};
