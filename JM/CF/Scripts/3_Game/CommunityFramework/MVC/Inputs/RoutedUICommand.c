

class RoutedCommandManager
{
	// Weak ref to RoutedCommand so its destroyed when UI's are
	static ref array<RoutedCommand> ActiveRoutedCommands = {};
}

class InputGestureCollection: ref set<KeyCode>
{
	bool Matches(set<KeyCode> key_codes)
	{
		int count = Count();
		foreach (KeyCode key: key_codes) {
			if (Find(key) != -1) {
				count--;
			}
		}
		
		return !count;
	}
}

class RoutedCommand
{
	protected string m_Name;
	string GetName() {
		return m_Name;
	}
	
	protected ref InputGestureCollection m_InputGestures;
	InputGestureCollection GetInputGestures() {
		return m_InputGestures;
	}
	
	void RoutedCommand(string name, InputGestureCollection input_gestures = null)
	{
		m_Name = name; m_InputGestures = input_gestures;
		RoutedCommandManager.ActiveRoutedCommands.Insert(this);
	}
}


class RoutedUICommand
{
	private bool m_CanExecute = true;
	
	protected ViewBinding m_ViewBinding;
	void SetViewBinding(ViewBinding view_binding) {
		m_ViewBinding = view_binding;
	}
	
	// returns bool defining whether or not the Execute can be called
	bool CanExecute() {
		return m_CanExecute;
	}
	
	// sets whether or not RoutedUICommand can be executed
	// depreciate if BI ever adds property Getters and Setters
	void SetCanExecute(bool state) {
		m_CanExecute = state;
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(CanExecuteChanged, m_CanExecute);
	}
	
	
	/* Abstract Methods */
	
	// called when type is Clicked, Selected, or Changed
	void Execute(RoutedUICommandArgs args);
	
	// Abstract function called when execution ability is changed
	void CanExecuteChanged(bool state);
}

