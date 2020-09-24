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
	protected ref ViewBindingHashMap m_ViewBindingHashMap;
	
	// View Bindings indexed by their Binding_Name
	protected ref DataBindingHashMap m_DataBindingHashMap;
	DataBindingHashMap GetDataBindings() {
		return m_DataBindingHashMap;
	}
	
	protected ref PropertyTypeHashMap m_PropertyTypeHashMap;
	
	void Controller()
	{		
		m_ViewBindingHashMap = new ViewBindingHashMap();
		m_DataBindingHashMap = new DataBindingHashMap();
		
		m_PropertyTypeHashMap = PropertyTypeHashMap.FromType(Type());
		m_PropertyTypeHashMap.RemoveType(Controller);
	}
	
	void ~Controller() 
	{ 
		delete m_ViewBindingHashMap;
		delete m_DataBindingHashMap;
		delete m_PropertyTypeHashMap;
	}
	
	override void OnWidgetScriptInit(Widget w)
	{		
		super.OnWidgetScriptInit(w);
		
		// Load all child Widgets and obtain their DataBinding class
		int binding_count = LoadDataBindings(m_LayoutRoot);
		Log("%1: %2 DataBindings found!", m_LayoutRoot.GetName(), binding_count.ToString());	
	}

	// Call this when you update a Controller property (variable)
	// Do NOT call this when using arrays / collections. Use ObservableCollection!
	void NotifyPropertyChanged(string property_name)
	{
		Trace("NotifyPropertyChanged " + property_name);
		ViewBindingArray views = m_DataBindingHashMap.Get(property_name);
	
		if (views) {
			foreach (ViewBinding view: views) {				
				view.UpdateView(this);
			}
		}

		PropertyChanged(property_name);
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

			view_binding.SetProperties(m_PropertyTypeHashMap.Get(view_binding.Binding_Name), m_PropertyTypeHashMap.Get(view_binding.Selected_Item));
			m_ViewBindingHashMap.Insert(w, view_binding);
			m_DataBindingHashMap.InsertView(view_binding);
		}
		
		if (w.GetChildren() != null)
			LoadDataBindings(w.GetChildren());
		
		
		if (w.GetSibling() != null) 
			LoadDataBindings(w.GetSibling());
		
		return m_DataBindingHashMap.Count();
	}
	
	// RoutedUICommand interfaces
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Trace("OnClick");
		ViewBinding view_binding = m_ViewBindingHashMap.Get(w);
		if (view_binding) {
			view_binding.UpdateModel(this);
			
			switch (w.Type()) {
				case ButtonWidget: {
					view_binding.InvokeCommand(new ButtonCommandArgs(ButtonWidget.Cast(w), button, ButtonWidget.Cast(w).GetState()));
					return true;
				}
			}
		} else {
			Log("View Binding not found!");
		}
			
		return super.OnClick(w, x, y, button);
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{	
		Trace("OnChange");
		
		ViewBinding view_binding = m_ViewBindingHashMap.Get(w);		
		if (view_binding) {
			view_binding.UpdateModel(this);
			switch (w.Type()) {
				
				case CheckBoxWidget: {
					view_binding.InvokeCommand(new CheckBoxCommandArgs(CheckBoxWidget.Cast(w), CheckBoxWidget.Cast(w).IsChecked()));
					return true;
				}
				
				case XComboBoxWidget: {
					view_binding.InvokeCommand(new XComboBoxCommandArgs(XComboBoxWidget.Cast(w), XComboBoxWidget.Cast(w).GetCurrentItem()));
					return true;
				}
			}
		} else {
			Log("View Binding not found!");
		}
		
		return super.OnChange(w, x, y, finished);
	}
}











