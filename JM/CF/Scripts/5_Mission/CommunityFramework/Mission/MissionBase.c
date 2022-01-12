modded class MissionBase
{
	void MissionBase()
	{
		CF_ModuleGameManager.UpdateGameFlag();

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
};