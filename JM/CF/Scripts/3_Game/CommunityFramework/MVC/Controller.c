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
class Controller: ScriptedViewBase
{	
	// All View Bindings
	protected autoptr ref ViewBindingHashMap m_ViewBindingHashMap = new ViewBindingHashMap();
	ViewBindingHashMap GetViewBindings() {
		return m_ViewBindingHashMap; 
	}
	
	ViewBinding GetViewBinding(Widget source) {
		return m_ViewBindingHashMap.Get(source);
	}
	
	// View Bindings indexed by their Binding_Name
	protected autoptr ref DataBindingHashMap m_DataBindingHashMap = new DataBindingHashMap();
	DataBindingHashMap GetDataBindings() {
		return m_DataBindingHashMap;
	}
		
	// Hashmap of all properties in the Controller
	protected autoptr ref PropertyTypeHashMap m_PropertyTypeHashMap = PropertyTypeHashMap.FromType(Type());
	
	// Hashmap of all relay commands in the ScriptView
	protected autoptr ref RelayCommandHashMap m_RelayCommandHashMap = new RelayCommandHashMap();
	
	
	override void OnWidgetScriptInit(Widget w)
	{		
		super.OnWidgetScriptInit(w);
		
		//m_PropertyTypeHashMap.RemoveType(Controller); crashing?
		
		// Load all child Widgets and obtain their DataBinding class
		int binding_count = LoadDataBindings(m_LayoutRoot);
		Log("%1: %2 DataBindings found!", m_LayoutRoot.GetName(), binding_count.ToString());	
	}
		
	// Call this when you update a Controller property (variable)
	// Do NOT call this when using arrays / collections. Use ObservableCollection!
	void NotifyPropertyChanged(string property_name, bool notify_controller = true)
	{
		Trace("NotifyPropertyChanged %1", property_name);
		ViewBindingArray views = m_DataBindingHashMap.Get(property_name);
	
		if (!views) return;
				
		foreach (ViewBinding view: views) {
			view.UpdateView(this);
		}
		
		if (notify_controller) {
			PropertyChanged(property_name);
		}
	}
	
	// Do NOT call this. ObservableCollection does this for you
	void NotifyCollectionChanged(string collection_name, CollectionChangedEventArgs args)
	{		
		Trace("NotifyCollectionChanged %1", collection_name);
		ViewBindingArray views = m_DataBindingHashMap.Get(collection_name);
				
		if (views) {
			foreach (ViewBinding view: views) {
				view.OnCollectionChanged(args);
			}
		}

		CollectionChanged(collection_name, args);
	}
	
	// Gets called every time a property is changed. 
	// Override this when you want to have an event AFTER property is changed
	void PropertyChanged(string property_name);
	
	// Gets called every time an observable collection is changed.
	// Override this when you want to have an event AFTER collection is changed
	void CollectionChanged(string collection_name, CollectionChangedEventArgs args);
	
	
	int LoadDataBindings(Widget w)
	{
		ViewBinding view_binding;
		w.GetScript(view_binding);
		
		if (view_binding && view_binding.IsInherited(ViewBinding)) {
			m_ViewBindingHashMap.Insert(w, view_binding);
			m_DataBindingHashMap.InsertView(view_binding);
			view_binding.SetProperties(m_PropertyTypeHashMap.Get(view_binding.Binding_Name), m_PropertyTypeHashMap.Get(view_binding.Selected_Item));
			
			
			if (view_binding.Relay_Command != string.Empty) {
				typename relay_command = view_binding.Relay_Command.ToType();
				if (relay_command && relay_command.IsInherited(RelayCommand)) {
					RelayCommand command = relay_command.Spawn();
					command.SetController(this);
					command.SetViewBinding(view_binding);
					view_binding.SetRelayCommand(command);
					m_RelayCommandHashMap.Insert(view_binding.Relay_Command, command);
				} else {
					Log("RelayCommand %1 not found on controller - Assuming its a function!", view_binding.Relay_Command);
				}
			}
			
			NotifyPropertyChanged(view_binding.Binding_Name);
		}
		
		
		// really wish i had XOR here
		bool b1 = (w.GetChildren() != null);
		bool b2 = (view_binding && view_binding.IsInherited(Controller) && view_binding != this);
		
		// scuffed XOR
		// Makes it stop loading when it finds another controller
		if (!(b1 && b2)) {
			if (b1 || b2) {
				LoadDataBindings(w.GetChildren());
			}
		}
		
		if (w.GetSibling() != null) {
			LoadDataBindings(w.GetSibling());
		}
		
		return m_DataBindingHashMap.Count();
	}

	
	// Command interfaces
	override bool OnClick(Widget w, int x, int y, int button)
	{		
		ViewBinding view_binding = m_ViewBindingHashMap.Get(w);	
		if (view_binding) {
			switch (w.Type()) {
				
				case ButtonWidget: { // only thing that isnt called in OnChange for some reason
					view_binding.UpdateController(this); 
					if (view_binding.InvokeCommand(this, new ButtonCommandArgs(w, button))) {
						return true;
					}
					break;
				}
			}
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		ViewBinding view_binding = m_ViewBindingHashMap.Get(w);	
		if (view_binding) {
			view_binding.UpdateController(this);
			switch (w.Type()) {
				case CheckBoxWidget: {
					if (view_binding.InvokeCommand(this, new CheckBoxCommandArgs(w, CheckBoxWidget.Cast(w).IsChecked()))) {
						return true;
					}
				}		
				

			}			
		}
				
		return super.OnChange(w, x, y, finished);
	}
	
	
	void DebugPrint()
	{
		m_DataBindingHashMap.DebugPrint();
	}
}











