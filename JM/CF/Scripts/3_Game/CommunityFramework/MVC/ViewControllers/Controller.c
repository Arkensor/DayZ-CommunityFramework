

// Abstract Class
class Controller: ScriptedWidgetEventHandler
{
	// Layout root - CAN be null
	protected Widget m_LayoutRoot;
		
	protected ref DataBindingHashMap m_ViewBindingHashMap = new DataBindingHashMap();
	protected ref PropertyHashMap m_PropertyHashMap = PropertyHashMap.FromType(Type());
	
	typename GetPropertyType(string property_name) {
		return m_PropertyHashMap.Get(property_name);
	}
	
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	void Controller() {
		MVC.Trace("Controller");
		if (Type() == Controller) {
			MVC.Error("You cannot bind to data without creating your own controller class!");
			return;
		}
	}
	
	void ~Controller() { 
		MVC.Trace("~Controller");
	}
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
		MVC.Trace("Controller::OnWidgetScriptInit %1", m_LayoutRoot.GetName());
	
		// Removes properties that only exist in the Controller type
		m_PropertyHashMap.RemoveType(Controller);
		
		MVC.Log("%1 properties found!", m_PropertyHashMap.Count().ToString());
		
		// Load all child Widgets and obtain their DataBinding class
		int binding_count = LoadDataBindings(m_LayoutRoot, m_ViewBindingHashMap);
		MVC.Log("%1: %2 DataBindings found!", m_LayoutRoot.GetName(), binding_count.ToString());
		
	
		// debug
		//m_ViewBindingHashMap.DebugPrint();
		
		
		/*
		foreach (string data_name, DataBindingBase data: m_DataBindingHashMap) {
			PropertyInfo prop = m_PropertyHashMap.GetPropertyInfo(data_name);
			if (!data.CanConvertFrom(prop.Type)) {
				ErrorDialog(string.Format("Invalid data type in %1. Found %2, supports %3", data_name, prop.Type, data.GetType()));
				m_DataBindingHashMap.Remove(data_name);
			}
		}*/
	}
	
	// This must be called manually by the user
	void NotifyPropertyChanged(string property_name)
	{
		//GetLogger().Log("Controller::NotifyPropertyChanged " + property_name, "JM_CF_MVC");
		ref ViewBindingSet view_set = m_ViewBindingHashMap.Get(property_name);
		
		if (view_set) 
			foreach (ViewBinding view: view_set)
				view.UpdateView();
			
		
		
		PropertyChanged(property_name);
	}
	
	// This gets called automatically when a collection is changed
	void NotifyCollectionChanged(string collection_name, CollectionChangedEventArgs args)
	{
		//GetLogger().Log("Controller::NotifyCollectionChanged " + collection_name, "JM_CF_MVC");
		ref ViewBindingSet view_set = m_ViewBindingHashMap.Get(collection_name);
		
		if (view_set) {
			foreach (ViewBinding view: view_set) {
				view.OnCollectionChanged(args);
			}
		}
		
		CollectionChanged(collection_name, args);
	}
	
	// Called every time a property is changed. 
	// Override this when you want to have an event AFTER property is changed
	void PropertyChanged(string property_name);
	
	// Called every time an observable collection is changed.
	// Override this when you want to have an event AFTER collection is changed
	void CollectionChanged(string collection_name, CollectionChangedEventArgs args);
	
	private int LoadDataBindings(Widget w, out DataBindingHashMap binding_map)
	{
		ViewBinding view_binding;
		w.GetScript(view_binding);
		
		if (view_binding && (view_binding.IsInherited(ViewBinding))) {
			binding_map.InsertView(view_binding);
			view_binding.SetController(this);
		}
		
		if (w.GetChildren() != null)
			LoadDataBindings(w.GetChildren(), binding_map);
		
		
		if (w.GetSibling() != null) 
			LoadDataBindings(w.GetSibling(), binding_map);
		
		return binding_map.Count();
	}
}











