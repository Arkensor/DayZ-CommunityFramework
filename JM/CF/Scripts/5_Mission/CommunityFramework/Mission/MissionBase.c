modded class MissionBase
{
	void MissionBase()
	{
		CreateDiscordManager();
		CreateSteamManager();

		new JMModuleConstructor();
	}
};