
// Check JM/CF/GUI/layouts/sample_mvc2.layout
class SampleScriptView: ScriptView
{
	
	// Commands
	protected ref SampleRelayCommand ButtonPressedCommand;
	
	Widget content_host;
	
	// Important for the Controller to get spawned
	override typename GetControllerType() {
		return SampleScriptViewController;
	}
	
	override string GetLayoutFile() {
		return "JM/CF/GUI/layouts/sample_mvc2.layout";
	}
}

class SampleScriptViewController: Controller
{
	
	
	// Properties
}

class SampleRelayCommand: RelayCommand
{
	
	override void Execute(CommandArgs args)
	{
		Print("SampleRelayCommand Execute!");
		SampleScriptView.Cast(m_ScriptView).content_host.Show(!SampleScriptView.Cast(m_ScriptView).content_host.IsVisible());
	
	}
}