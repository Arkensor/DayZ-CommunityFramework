
enum NotifyCollectionChangedAction {
	Add,
	Remove,
	Set,
	Move,
	Clear
};


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



// 0: Property Name
// 1: Proprety Type
class PropertyHashMap: ref map<string, typename>
{
	static ref PropertyHashMap FromType(typename type)
	{
		ref PropertyHashMap hash_map = new PropertyHashMap();
		for (int i = 0; i < type.GetVariableCount(); i++) {
			hash_map.Insert(type.GetVariableName(i), type.GetVariableType(i));	
		}
		
		return hash_map;
	}
}


// 0: Property Name
// 1: View Binding
typedef ref set<ref ViewBinding> ViewBindingSet;
class ViewBindingHashMap: ref map<Widget, ref ViewBindingSet>
{
	void DebugPrint()
	{
		foreach (Widget w, ViewBindingSet view_set: this) {
			PrintFormat("[%1]:", w.GetName()); 
			foreach (ViewBinding view: view_set) {
				PrintFormat("    %1", view.GetLayoutRoot().GetName());
			}
		}		
	}
	
	void InsertView(ViewBinding view)
	{
		Widget key = view.GetLayoutRoot();
		ViewBindingSet view_set = Get(key);
		if (!view_set) {
			view_set = new ViewBindingSet();
			view_set.Insert(view);
			Insert(key, view_set);
		} else {
			view_set.Insert(view);
		}		
	}
}

class DataBindingHashMap: ref map<string, ref ViewBindingSet>
{
	void DebugPrint()
	{
		foreach (string name, ViewBindingSet view_set: this) {
			PrintFormat("[%1]:", name); 
			foreach (ViewBinding view: view_set) {
				PrintFormat("    %1", view.GetLayoutRoot().GetName());
			}
		}
	}
	
	void InsertView(ViewBinding view)
	{
		string key = view.GetBindingName();
		ViewBindingSet view_set = Get(key);
		if (!view_set) {
			view_set = new ViewBindingSet();
			view_set.Insert(view);
			Insert(key, view_set);
		} else {
			view_set.Insert(view);
		}		
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
	Class Context;
	Param CommandArgs;
	typename CommandArgsType;
	
	void RelayCommandArgs(Class context, Param command_args)
	{
		Context = context;
		CommandArgs = command_args;
		CommandArgsType = CommandArgs.Type();
	}
	
}


enum WidgetEventType { // unused
	WidgetEventChange,
	WidgetEventChildAdd,
	WidgetEventChildRemove,
	WidgetEventClick,
	WidgetEventController,
	WidgetEventDrag,
	WidgetEventDragging,
	WidgetEventDraggingOver,
	WidgetEventDrop,
	WidgetEventDropReceived,
	WidgetEventFocus,
	WidgetEventFocusLost,
	WidgetEventItemSelected,
	WidgetEventItemSelectedTypeID,
	WidgetEventKeyDown,
	WidgetEventKeyPress,
	WidgetEventModalResult,
	WidgetEventMouseButtonDown,
	WidgetEventMouseButtonUp,
	WidgetEventMouseDoubleClick,
	WidgetEventMouseEnter,
	WidgetEventMouseLeave,
	WidgetEventMouseMove,
	WidgetEventMouseWheel,
	WidgetEventResize,
	WidgetEventSliderChange,
	WidgetEventUpdate	
};


