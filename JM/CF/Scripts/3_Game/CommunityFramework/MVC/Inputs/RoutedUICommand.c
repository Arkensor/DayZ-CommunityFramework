


class InputGestureCollection: ref map<KeyCode, bool>
{
	
	static InputGestureCollection CreateFromKeyCodes(array<KeyCode> keys)
	{
		Print(keys);
		Print("tyleriscool");
		InputGestureCollection collection = new InputGestureCollection();
		foreach (KeyCode key: keys) {
			collection.Insert(key, true);
		}
		Print(collection[0]);
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
	private bool m_CanExecute = true;
	
	protected ViewBinding m_ViewBinding;
	void SetViewBinding(ViewBinding view_binding) {
		m_ViewBinding = view_binding;
	}
	
	// sets whether or not RoutedUICommand can be executed
	// depreciate if BI ever adds property Getters and Setters
	void SetCanExecute(bool state) {
		m_CanExecute = state;
		GetWorkbenchGame().GetCallQueue(CALL_CATEGORY_GUI).Call(CanExecuteChanged, m_CanExecute);
	}
	
	bool CanExecute() {
		return m_CanExecute;
	}
	
	InputGestureCollection GetInputGestures() {
		return InputGestureCollection.CreateFromKeyCodes(GetKeys());
	}
	
	
	/* Abstract Methods */
	
	// should return the key combos required to activate the command
	ref array<KeyCode> GetKeys();
	
	// should return the Name of the Command
	string GetName();
	
	// called when type is Clicked, Selected, or Changed
	void Execute(RoutedUICommandArgs args);
	
	// Abstract function called when execution ability is changed
	void CanExecuteChanged(bool state);
	
	//event void CanExecuteChanged();
}

