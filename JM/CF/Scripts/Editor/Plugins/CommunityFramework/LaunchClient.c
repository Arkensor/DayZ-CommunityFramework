
[WorkbenchPluginAttribute("Launch Client", "Launches the game", "F8", "", {"ResourceManager", "ScriptEditor"})]
class LaunchClientModTool: DayZProjectManager
{
	override void Run()
	{
		RunDayZBat(string.Format("P:\\%1\\Workbench\\Batchfiles\\LaunchClient.bat", ModName), true);
	}
}



