modded class MissionBase
{
	protected bool m_bLoaded = false;
	
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

		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
	}
};
