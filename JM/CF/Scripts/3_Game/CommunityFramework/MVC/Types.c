
// 0: Property Name
// 1: Proprety Type
class PropertyTypeHashMap: ref map<string, typename>
{
	static ref PropertyTypeHashMap FromType(typename type)
	{
		ref PropertyTypeHashMap hash_map = new PropertyTypeHashMap();
		for (int i = 0; i < type.GetVariableCount(); i++) {
			hash_map.Insert(type.GetVariableName(i), type.GetVariableType(i));	
		}
		
		return hash_map;
	}
	
	void RemoveType(typename removed_type)
	{
		PropertyTypeHashMap hash_map = FromType(removed_type);
		foreach (string name, typename type: hash_map)
			Remove(name);
	}
}


// 0: Property Name
// 1: View Binding
typedef ref set<ref ViewBinding> ViewBindingSet;


// 0: Property Name
// 1: View Binding Set
class DataBindingHashMap: ref map<string, ref ViewBindingSet>
{
	void DebugPrint()
	{
		foreach (string name, ViewBindingSet view_set: this) {
			MVC.Log("[%1]:", name);
			foreach (ViewBinding view: view_set) {
				MVC.Log("    %1", view.GetLayoutRoot().GetName());
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


