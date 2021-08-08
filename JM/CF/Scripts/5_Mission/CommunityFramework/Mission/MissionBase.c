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

		CF._MissionInit();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF._MissionCleanup();
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