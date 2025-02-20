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

#ifndef DAYZ_1_26
	//! 1.27+
	void ~MissionBase()
	{
		CF_ModuleCoreManager._UnloadScriptModules({"Mission"});
	}
#endif

	void OnMissionLoaded()
	{
	}

	void CF_OnUpdate(float timeslice)
	{
#ifdef SERVER
		float updateTime = GetGame().GetTickTime();
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
			OnMissionLoaded();
		}

#ifdef SERVER
		if (update)
		{
			CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(elapsed));
		}
#else
		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
#endif
	}
};
