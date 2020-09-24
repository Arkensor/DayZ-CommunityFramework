
// Check JM/CF/GUI/layouts/sample_mvc2.layout
class SampleScriptViewController: Controller
{
	Widget content_host;
	
	ref SampleScriptView script_view;
}

class SampleRelayCommand: RelayCommand
{
	
	override void Execute(CommandArgs args)
	{
		Print("SampleRelayCommand Execute!");
		SampleScriptViewController controller = SampleScriptViewController.Cast(m_Controller);
		
		if (ButtonWidget.Cast(args.Source).GetState()) {
			controller.script_view = new SampleScriptView(controller.content_host);
		} else {
			delete controller.script_view;
		}
	}
}


// This is just a wrapper for JM/CF/GUI/layouts/sample_mvc.layout
class SampleScriptView: ScriptView
{
	override string GetLayoutFile() {
		return "JM/CF/GUI/layouts/sample_mvc.layout";
	}
	
	override typename GetControllerType() {
		return SampleScriptViewController;
	}
}