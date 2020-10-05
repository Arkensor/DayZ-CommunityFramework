[WorkbenchPluginAttribute("LayoutBindingManager Settings", "Edit LayoutBindingManager Settings", "", "", {"ResourceManager", "ScriptEditor"})]
class LayoutBindingManagerPlugin: WorkbenchPlugin
{
	[Attribute("", "combobox", "", "", ParamEnumArray.FromEnum(LogLevel))]
	int Log_Level;
	
	override void Run()
	{
		Log_Level = LBMLogLevel;
		Workbench.ScriptDialog("Edit LayoutBindingManager Settings", "", this);
	}
	
	[ButtonAttribute("OK")]
	void DialogOk()
	{
		LBMLogLevel = Log_Level;
	}
		
	[ButtonAttribute("Cancel")]
	void DialogCancel()
	{
		
	}
};