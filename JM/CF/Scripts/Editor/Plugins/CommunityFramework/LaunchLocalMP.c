
[WorkbenchPluginAttribute("Launch Local MP", "Launches the server and client, automatically joins", "F6", "", {"ResourceManager", "ScriptEditor"})]
class LaunchLocalMPModTool: DayZProjectManager
{
	override void Run()
	{
		RunDayZBat(string.Format("P:\\%1\\Workbench\\Batchfiles\\LaunchLocalMP.bat", ModName), true);
	}
}



