
// Event Args for Collection Changed
// 0: Collection that was changed
// 1: Collection Changed Action
// 2: Collection Changed Index
// 3: Collection Changed Value
class CollectionChangedEventArgs: Param4<Class, int, int, ref Param>
{
	Observable GetCollection() {
		return Observable.Cast(param1);
	}
	
	NotifyCollectionChangedAction GetChangedAction() {
		return param2;
	}
	
	int GetChangedIndex() {
		return param3;
	}
	
	Param GetChangedValue() {
		return param4;
	}
}



// Event Args for Property Changed
// 0: Name of property changed
// 1: New property value
class PropertyChangedEventArgs: Param2<string, Class>
{
	string GetPropertyName() {
		return param1;
	}
	
	Class GetPropertyValue() {
		return param2;
	}
}


// 0: Source Widget
// 1: Mouse Button
// 2: Button State
class ButtonCommandArgs: Param3<ButtonWidget, int, bool>
{
	ButtonWidget GetButtonWidget() { 
		return param1; 
	}
	
	int GetMouseButton() {
		return param2;
	}
	
	bool GetButtonState() {
		return param3;
	}
}


// 0: Source Widget
// 1: CheckBox State
class CheckBoxCommandArgs: Param2<CheckBoxWidget, bool>
{
	CheckBoxWidget GetCheckBoxWidget() {
		return param1;
	}
	
	bool GetCheckBoxState() {
		return param2;
	}
}

// 0: Source Widget
// 1: Selected Item
class XComboBoxCommandArgs: Param2<XComboBoxWidget, int>
{
	XComboBoxWidget GetComboBoxWidget() {
		return param1;
	}
	
	int GetSelectedIndex() {
		return param2;
	}
}

// 0: Source Widget
// 1: Selected Widget
class WrapSpacerCommandArgs: Param2<WrapSpacerWidget, Widget>
{
	WrapSpacerWidget GetWrapSpacerWidget() {
		return param1;
	}
	
	Widget GetSelectedWidget() {
		return param2;
	}
}

// 0: Call Context
// 1: Command Args (see above)
class RelayCommandArgs
{
	ViewBinding Context;
	Param CommandArgs;
	typename CommandArgsType;
	
	void RelayCommandArgs(ViewBinding context, Param command_args)
	{
		Context = context;
		CommandArgs = command_args;
		if (CommandArgs)
			CommandArgsType = CommandArgs.Type();
	}	
}

class CanExecuteEventArgs
{
	RelayCommand Command;
	bool CanExecute = true;
}