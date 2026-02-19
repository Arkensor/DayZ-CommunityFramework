modded class MissionBase
{
#ifdef SERVER
	float m_CF_UpdateTime;
#endif

	CF_EventUpdateArgs m_CF_EventUpdateArgs = new CF_EventUpdateArgs;

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

	void ~MissionBase()
	{
#ifndef DAYZ_1_26
		//! 1.27+
		CF_ModuleCoreManager._UnloadScriptModules({"Mission"});
#endif

		delete m_CF_EventUpdateArgs;
	}

	void OnMissionLoaded()
	{
	}

	void CF_OnUpdate(float timeslice)
	{
#ifdef SERVER
		float updateTime = g_Game.GetTickTime();
		float elapsed = updateTime - m_CF_UpdateTime;
		bool update = elapsed >= 0.025;

		if (update)
		{
			m_CF_UpdateTime = updateTime;
		}
#endif

		if (!m_bLoaded)
		{
			if (g_Game.IsLoading())
			{
				return;
			}

			m_bLoaded = true;
			CF_ModuleGameManager.UpdateGameFlag();
			OnMissionLoaded();
		}

#ifdef SERVER
		if (update)
		{
			m_CF_EventUpdateArgs.DeltaTime = elapsed;
			CF_ModuleGameManager.OnUpdate(this, m_CF_EventUpdateArgs);
		}
#else
		m_CF_EventUpdateArgs.DeltaTime = timeslice;
		CF_ModuleGameManager.OnUpdate(this, m_CF_EventUpdateArgs);
#endif
	}

	override bool CF_IsLoaded()
	{
		return m_bLoaded;
	}
};
