[WorkbenchPluginAttribute("Build Mod", "Builds current mod", "F3", "", {"ResourceManager", "ScriptEditor"})]
class BuildMod: DayZProjectManager
{
	override void Run()
	{
		RunDayZBatList({
			string.Format("P:\\%1\\Workbench\\Batchfiles\\Exit.bat", ModName), 
			string.Format("P:\\%1\\Workbench\\Batchfiles\\ZBinarizeDeploy.bat", ModName)
		});
	}
}