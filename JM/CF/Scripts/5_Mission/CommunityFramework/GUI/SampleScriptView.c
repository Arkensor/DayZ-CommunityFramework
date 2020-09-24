
// Check JM/CF/GUI/layouts/sample_mvc2.layout
class SampleScriptViewController: Controller
{
	Widget content_host;
	
	ref ObservableCollection<ref SampleScriptView> script_view = new ObservableCollection<ref SampleScriptView>("script_view", this);
}

class SampleRelayCommand: RelayCommand
{
	override void Execute(CommandArgs args)
	{ 
		Print("SampleRelayCommand Execute!");
		SampleScriptViewController controller = SampleScriptViewController.Cast(m_Controller);
				
		if (ButtonWidget.Cast(args.Source).GetState()) {
			controller.script_view.Insert(new SampleScriptView());
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