
// Weak ref to RoutedCommand so its deleted when ViewBinding dies
typedef ref map<int, RoutedUICommand> RoutedCommandMap;


class CommandManager
{
	static ref RoutedCommandMap RoutedCommands = new RoutedCommandMap();
	
	RoutedUICommand Get(string command_name) {
		RoutedUICommand command;
		EnScript.GetClassVar(this, command_name, 0, command);
		return command;
	}
}



// 0: KeyCodes OR'd
// 1: State of key
class InputGestureCollection: ref map<int[], bool>
{
	/*
	static InputGestureCollection CreateFromKeyCodes(array<KeyCode> keys)
	{
		InputGestureCollection collection = new InputGestureCollection();
		foreach (KeyCode key: keys) {
			collection.Insert(key, true);
		}
		return collection;
	}*/
	
	static InputGestureCollection Create(int keys)
	{
		InputGestureCollection collection = new InputGestureCollection();
		collection.Insert(keys, true);
		return collection;
	}
	
	
	
	/*	
	bool Matches(set<KeyCode> key_codes)
	{
		set<KeyCode> copy_set;
		copy_set.Copy(this);
		foreach (KeyCode key: key_codes) {
			copy_set.Remove(Find(key));
		}
		
		return (copy_set.Count() == 0);
	}*/
	
	string GetInputString()
	{
		string result;
		foreach (KeyCode key, bool value: this) {
			result += typename.EnumToString(KeyCode, key);
		}
		
		return result;
	}
}





class RoutedUICommand
{
	private int KeyStorage;
	private ref array<KeyCode> m_InputGestures;
	
	string Text;
	string Name;
	
	void RoutedUICommand(string text = "", string name = "", ref array<KeyCode> input_gestures = null)
	{		
		Text = text;
		Name = name;
		m_InputGestures = input_gestures;
		foreach (KeyCode key: input_gestures) {
			KeyStorage |= key;
		}

		CommandManager.RoutedCommands.Insert(KeyStorage, this);
	}
		
	protected ViewBinding m_ViewBinding;
	void SetViewBinding(ViewBinding view_binding) {
		m_ViewBinding = view_binding;
	}
		
	// string representation of shortcut keys 
	// i.e. Ctrl + Shift + T
	string GetKeyString() {
		string result;
		int i = 0;
		foreach (KeyCode key: m_InputGestures) {
			
			string keyname = typename.EnumToString(KeyCode, key);
			keyname.Replace("KC_", "");			
			switch (keyname) {
				
				case "LCONTROL": {
					keyname = "LCtrl";
					break;
				}
				
				case "LMENU": {
					keyname = "LAlt";
					break;
				}
			}
			
			i++;
			if (i != m_InputGestures.Count())
				result += keyname + " + ";
			else result += keyname;
		}
		
		return result;
	}
	
	// called when type is Clicked, Selected, or Changed
	// (RoutedUICommandArgs args)
	ref ScriptInvoker Execute = new ScriptInvoker();
	
	// called on load to check if you it should be executable
	// (Class context, out CanExecuteEventArgs e)
	ref ScriptInvoker CanExecute = new ScriptInvoker();
	
	// Abstract function called when execution ability is changed
	// (bool state)
	ref ScriptInvoker CanExecuteChanged = new ScriptInvoker();
	
}

