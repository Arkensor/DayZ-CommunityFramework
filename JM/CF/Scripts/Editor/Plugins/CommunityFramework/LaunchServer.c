
[WorkbenchPluginAttribute("Launch Client", "Launches the game", "F9", "", {"ResourceManager", "ScriptEditor"})]
class LaunchServerModTool: DayZProjectManager
{
	override void Run()
	{
		RunDayZBat(string.Format("P:\\%1\\Workbench\\Batchfiles\\LaunchServer.bat", ModName), true);
	}
}



