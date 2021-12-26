modded class MissionBase
{
	void MissionBase()
	{
		CreateDiscordManager();
		CreateSteamManager();

		CreateModuleManager(new JMModuleConstructor);
	}
};