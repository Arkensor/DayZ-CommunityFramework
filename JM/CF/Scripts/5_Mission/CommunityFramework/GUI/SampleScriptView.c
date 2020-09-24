
// Check JM/CF/GUI/layouts/sample_mvc2.layout
class SampleScriptView: ScriptView
{
	
	// Important for the Controller to get spawned
	override typename GetControllerType() {
		return SampleScriptViewController;
	}
	
	override string GetLayoutFile() {
		return "JM/CF/GUI/layouts/sample_mvc.layout";
	}
}

class SampleScriptViewController: Controller
{
	// Commands
	protected ref SampleRelayCommand ButtonPressedCommand;
}

class SampleRelayCommand: RelayCommand
{
		
	override void Execute(CommandArgs args)
	{
		Print("SampleRelayCommand Execute!");
	}
}