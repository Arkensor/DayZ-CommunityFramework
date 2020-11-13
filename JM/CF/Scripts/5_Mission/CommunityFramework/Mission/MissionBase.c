modded class MissionBase
{
	void MissionBase()
	{
		CreateDiscordManager();
		CreateSteamManager();

		//! Create module manager before _MissionInit as a fallback for old permissions code
		if ( !ModuleManagerExists() )
		{
			Print( "Creating ModuleManager" );

			CreateModuleManager( new JMModuleConstructor );
		} else
		{
			Print( "Ignoring creation of ModuleManager" );
		}

		CF._MissionInit();
	}
};