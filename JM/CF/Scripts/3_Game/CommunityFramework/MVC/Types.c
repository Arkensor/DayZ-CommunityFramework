

// 0: Property Name
// 1: Property Type
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

typedef map<typename, typename> TypenameHashMap;
class TypeConversionHashMap
{
	private ref map<typename, typename> value = new map<typename, typename>();
	
	
	typename Get(typename conversion_type) {
		return value.Get(conversion_type);
	}
	
	void Remove(typename conversion_type) {
		value.Remove(conversion_type);
	}
	
	void Set(typename conversion_type, typename conversion_class)
	{
		//GetLogger().Log("TypeConverterHashMap::Set", "JM_CF_MVC");
		if (!conversion_class.IsInherited(TypeConversionTemplate)) {
			MVC.Error(string.Format("TypeConverterHashMap: %1 must inherit from type TypeConversionTemplate", conversion_class.ToString()));
			return;
		}
		
		value.Set(conversion_type, conversion_class);
	} 
	
	bool Insert(typename conversion_type, typename conversion_class)
	{
		//GetLogger().Log("TypeConverterHashMap::Insert", "JM_CF_MVC");
		if (!conversion_class.IsInherited(TypeConversionTemplate)) {
			MVC.Error(string.Format("TypeConverterHashMap: %1 must inherit from type TypeConversionTemplate", conversion_class.ToString()));
			return false;
		}
		
		return value.Insert(conversion_type, conversion_class);
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


