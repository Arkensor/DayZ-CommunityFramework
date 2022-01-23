modded class MissionBase
{
	protected bool m_CF_MissionLoaded = false;
	
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

		if (!m_CF_MissionLoaded)
		{
			m_CF_MissionLoaded = true;
			OnMissionLoaded();
		}

		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
	}
};
