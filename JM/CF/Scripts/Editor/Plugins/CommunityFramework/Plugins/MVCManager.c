[WorkbenchPluginAttribute("MVC Settings", "Edit MVC Settings", "", "", {"ResourceManager", "ScriptEditor"})]
class MVCManager: WorkbenchPlugin
{
	[Attribute("", "combobox", "", "", ParamEnumArray.FromEnum(LogLevel))]
	int Log_Level;
	
	override void Configure()
	{
		Workbench.ScriptDialog("Edit MVC Settings", "", this);
		MVCLogLevel = Log_Level;
	}
}
 