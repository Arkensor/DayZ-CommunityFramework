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

		GetRPCManager().AddRPC("CF", "CF_DebugUIState", this, SingeplayerExecutionType.Client);
	}

	void ~MissionBase()
	{
        CF._MissionCleanup();
	}

	void OnMissionLoaded()
	{
		CF._MissionInit();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF._MissionCleanup();
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

	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		UIScriptedMenu menu = NULL;

		switch (id)
		{
		case CF_MVVM.MVVM_UI_MENU_ID:
			menu = new CF_MVVM_Menu();
			break;
		}

		if (menu)
		{
			menu.SetID(id);
		}
		else
		{
			menu = super.CreateScriptedMenu(id);
		}

		return menu;
	}

	void CF_DebugUIState(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<bool> data;
		if (!ctx.Read(data)) return;

		if (type == CallType.Server) return;

		CF_Debug.SetAllowed(data.param1);
	}

	void CF_SendDebugUIState(PlayerIdentity target)
	{
		GetRPCManager().SendRPC("CF", "CF_DebugUIState", new Param1<bool>(CF_Debug.IsAllowed()), true, target);  
	}
	
	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		return false;
	}
};
