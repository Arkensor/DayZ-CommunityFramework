[WorkbenchPluginAttribute("Launch Offline", "Launches the game in offline mode", "alt+3", "", {"ResourceManager", "ScriptEditor"})]
class LaunchOfflineModTool: DayZTool
{
	string BatchFile;

	void LaunchOfflineModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchOffline.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}