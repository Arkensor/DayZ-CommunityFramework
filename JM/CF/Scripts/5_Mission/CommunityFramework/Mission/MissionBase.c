modded class MissionBase
{
	void MissionBase()
	{
		CreateDiscordManager();
		CreateSteamManager();

		if ( !ModuleManagerExists() )
		{
			Print( "Creating ModuleManager" );

			CreateModuleManager( new JMModuleConstructor );
		} else
		{
			Print( "Ignoring creation of ModuleManager" );
		}

		GetRPCManager().AddRPC("CF", "CF_DebugUIState", this, SingeplayerExecutionType.Client);
	}

	void OnMissionLoaded()
	{
		CF._MissionInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF._MissionCleanup();
	}

	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		UIScriptedMenu menu = NULL;

		switch (id)
		{
		case __Constants.CF_MVVM_MENU:
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