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
};