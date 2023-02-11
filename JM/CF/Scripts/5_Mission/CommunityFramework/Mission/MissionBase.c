modded class MissionBase
{
#ifdef SERVER
	static const float CF_UPDATEINTERVAL = 0.025;
#else
	static const float CF_UPDATEINTERVAL = 0.005;
#endif

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
		if (!m_bLoaded)
		{
			if (g_Game.IsLoading())
			{
				return;
			}

			m_bLoaded = true;
			OnMissionLoaded();
		}

		m_CF_UpdateTime += timeslice;

		if (m_CF_UpdateTime >= CF_UPDATEINTERVAL)
		{
			CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(m_CF_UpdateTime));

			m_CF_UpdateTime = 0;
		}
	}
};
