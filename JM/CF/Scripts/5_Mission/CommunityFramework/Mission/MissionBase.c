modded class MissionBase
{
#ifdef SERVER
	float m_CF_UpdateTime;
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

#ifdef SERVER
		m_CF_UpdateTime += timeslice;

		if (m_CF_UpdateTime >= 0.025)
		{
			CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(m_CF_UpdateTime));

			m_CF_UpdateTime = 0;
		}
#else
		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
#endif
	}
};
