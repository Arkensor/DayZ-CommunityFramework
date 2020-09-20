/*

Controller Class Example:

class TestController: Controller
{
	// "TextBox1" goes into Binding_Name
	string TextBox1 = "TextBox1Text";
	
	// "TextBox2" goes into Binding_Name
	int TextBox2;
	
	// "WindowButton1" goes into Binding_Name
	bool WindowButton1; 
	
	
	// If WindowButton1 is bound to a button,
	// call this function and it will
	// set the state of the button on your UI
	void SetWindowButton1(bool state)
	{
		WindowButton1 = state;
		NotifyPropertyChanged("WindowButton1");
	}
	
	// Gets called whenever a property was changed in the controller
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "WindowButton1": {
				Print("WindowButton1 " + WindowButton1);
				break;
			}
		}
	}
}
*/


// Abstract Class
class Controller: ScriptedWidgetEventHandler
{
	// Layout root - CAN be null
	protected Widget m_LayoutRoot;
		
	protected ref DataBindingHashMap m_ViewBindingHashMap = new DataBindingHashMap();
	protected ref PropertyTypeHashMap m_PropertyTypeHashMap = PropertyTypeHashMap.FromType(Type());
	
	
	
	typename GetPropertyType(string property_name) {
		return m_PropertyTypeHashMap.Get(property_name);
	}
		
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	void Controller() 
	{
		MVC.Trace("Controller");
		if (Type() == Controller) {
			MVC.Error("You cannot bind to data without creating your own controller class!");
			return;
		}
	}
	
	void ~Controller() 
	{ 
		MVC.Trace("~Controller");
	}
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
		MVC.Trace("Controller::OnWidgetScriptInit %1", m_LayoutRoot.GetName());
		
		m_PropertyTypeHashMap.RemoveType(Controller);
		
		// Load all child Widgets and obtain their DataBinding class
		int binding_count = LoadDataBindings(m_LayoutRoot, m_ViewBindingHashMap);
		MVC.Log("%1: %2 DataBindings found!", m_LayoutRoot.GetName(), binding_count.ToString());

#ifdef COMPONENT_SYSTEM
		//Workbench.Dialog("Read the docs!", "Documentation available here\nhttps:\/\/www.twitch.tv/InclementDab\n");
#endif
	
	}
	
	// Call this when you update a Controller property (variable)
	// Do NOT call this when using arrays / collections.
	// Use ObservableCollection!
	void NotifyPropertyChanged(string property_name)
	{
		MVC.Trace("Controller::NotifyPropertyChanged " + property_name);
		ViewBindingSet view_set = m_ViewBindingHashMap.Get(property_name);
		
		if (view_set) 
			foreach (ViewBinding view: view_set)
				view.UpdateView();

		PropertyChanged(property_name);
	}
	
	
	// This gets called automatically when a collection is changed
	void NotifyCollectionChanged(string collection_name, CollectionChangedEventArgs args)
	{		
		MVC.Trace("Controller::NotifyCollectionChanged %1", collection_name);
		ref ViewBindingSet view_set = m_ViewBindingHashMap.Get(collection_name);
				
		if (view_set) 
			foreach (ViewBinding view: view_set) 
				view.OnCollectionChanged(args);

		CollectionChanged(collection_name, args);
	}
	
	// Gets called every time a property is changed. 
	// Override this when you want to have an event AFTER property is changed
	void PropertyChanged(string property_name);
	
	// Gets called every time an observable collection is changed.
	// Override this when you want to have an event AFTER collection is changed
	void CollectionChanged(string collection_name, CollectionChangedEventArgs args);
	
	int LoadDataBindings(Widget w) {
		return LoadDataBindings(w, m_ViewBindingHashMap);
	}
	
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











