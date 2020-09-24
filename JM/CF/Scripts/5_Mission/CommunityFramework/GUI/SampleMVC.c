
class SampleRelayCommand: RelayCommand
{
	
	override void Execute(RelayCommandArgs args)
	{
		
	}
}

class SampleView: ScriptView
{
	// MUST be ref
	protected ref SampleRelayCommand ButtonPressedCommand;
	
}

class SampleController: Controller
{
	float slider_value = 25; // default value will be 25
	float progress_value = 75;
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "slider_value": {
				// sets progress bar to move opposite of the slider
				progress_value = Math.AbsFloat(slider_value - 100); 
				// MUST be called when changing a property, notifies the UI that something changed!
				NotifyPropertyChanged("progress_value"); 
				break;
			}
		}
	}
}

class SampleSubController: Controller
{
	bool button_state;
	
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			

			
		}
	}
}