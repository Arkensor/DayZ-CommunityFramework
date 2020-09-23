

class ViewBinding: ScriptedViewBase
{	
	// Name of Variable to bind to
	protected reference string Binding_Name;	
	string GetBindingName() { 
		return Binding_Name; 
	}
		
	// Name of Variable to bind "selected item" to...
	// Only valid if type is ObservableCollection
	protected reference string Selected_Item;
	
	// If true, Bindings go both ways. Otherwise the controller is the master
	protected reference bool Two_Way_Binding;
	
	// Name of RoutedUICommand class that is controlled by ViewBinding
	// Can be either name of Class that inherits from RoutedUICommand, OR a function within the controller
	protected reference string Relay_Command;
	
	protected reference string Relay_Execute;
	
	protected reference string Relay_CanExecute;
	
	protected reference string Relay_ExecuteChanged;

	// Weak reference to Parent controller	
	protected Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}

	// Weak reference to Routed Command
	protected RoutedUICommand m_RoutedUICommand;
	RoutedUICommand GetRoutedUICommand() {
		return m_RoutedUICommand;
	}
	
	protected autoptr ref TypeConverter 	m_PropertyConverter;
	protected autoptr ref TypeConverter 	m_SelectedPropertyConverter;
	
	protected autoptr ref WidgetController 	m_WidgetController;
	
	protected typename m_PropertyType;
	protected typename m_SelectedPropertyType;	
	
	void OnWidgetScriptInit(Widget w)
	{
		MVC.Trace("ViewBinding::OnWidgetScriptInit %1", w.GetName());
		
		m_LayoutRoot = w;
		if (!m_LayoutRoot) {
			MVC.Error("ViewBinding: Layout was null!");
			return;
		}
		
		m_LayoutRoot.SetHandler(this);
		if (Relay_Command != string.Empty) {
			SetRoutedUICommand(Relay_Command);
		}
		
		m_WidgetController = MVC.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController) {
			MVC.Error("ViewBinding: Could not find WidgetController for type %1\nOverride MVC.RegisterWidgetControllers to register custom WidgetControllers", m_LayoutRoot.GetTypeName());
			return;
		}
		
		// Check for two way binding support
		if (Two_Way_Binding && !m_WidgetController.CanTwoWayBind()) {
			MVC.Log("ViewBinding: Two Way Binding for %1 is not supported!", m_LayoutRoot.Type().ToString());
		}
	}
	
	void SetController(Controller controller) 
	{ 
		MVC.Trace("ViewBinding::SetController");
		m_Controller = controller;
	
		if (!m_Controller) {
			MVC.Error("Controller is null!");
			return;
		}
		
		// This is going to log all the time, even if you arent using DataBinding
		m_PropertyType = m_Controller.GetPropertyType(Binding_Name);
		if (!m_PropertyType) {
			MVC.Log("ViewBinding: Binding Property '%1' not found", Binding_Name);
		} else {
			m_PropertyConverter = MVC.GetTypeConversion(m_PropertyType);
			if (!m_PropertyConverter) {
				MVC.Error("Could not find TypeConverter for type %1\nOverride MVC.RegisterConversionTemplates to register custom TypeConverters", m_PropertyType.ToString());
				return;
			}
		}
	
		if (Selected_Item != string.Empty) {
			m_SelectedPropertyType = m_Controller.GetPropertyType(Selected_Item);
			if (m_SelectedPropertyType) {
				m_SelectedPropertyConverter = MVC.GetTypeConversion(m_SelectedPropertyType);
				if (!m_SelectedPropertyConverter) {
					MVC.Error("Property '%1' not found", Selected_Item);
					return;
				}
			} else {
				MVC.Log("ViewBinding: Selected Item Property '%1' not found", Selected_Item);
			}
		}
		
		// Updates the view on first load
		UpdateView();
	}
	
	private bool IsInitialized() {
		return (m_Controller && m_WidgetController);
	}

	void OnCollectionChanged(ref CollectionChangedEventArgs args)
	{
		if (!m_WidgetController) return;
		MVC.Trace("Updating Collection View: %1", m_LayoutRoot.Type().ToString());

		// We dont want to work with type Observable for everything
		TypeConverter collection_converter = MVC.GetTypeConversion(args.GetCollection().GetType());
		if (!collection_converter) return;

		// Anonymous Data Setter
		if (args.GetChangedValue())
			collection_converter.SetParam(args.GetChangedValue());
		
		switch (args.GetChangedAction()) {
						
			case NotifyCollectionChangedAction.Add: {
				m_WidgetController.InsertData(args.GetChangedIndex(), collection_converter);
				break;
			}
			
			case NotifyCollectionChangedAction.Remove: {
				m_WidgetController.RemoveData(args.GetChangedIndex(), collection_converter);
				break;
			}
			
			case NotifyCollectionChangedAction.Set: {
				m_WidgetController.ReplaceData(args.GetChangedIndex(), collection_converter);
				break;
			}
			
			case NotifyCollectionChangedAction.Move: {
				// this ones a weird case /shrug
				m_WidgetController.MoveData(args.GetChangedIndex(), Param1<int>.Cast(args.GetChangedValue()).param1);
				break;	
			}
			
			case NotifyCollectionChangedAction.Clear: {
				m_WidgetController.ClearData();
				break;
			}
		}
	}

	void UpdateView()
	{
		if (!IsInitialized()) return;
		MVC.Trace("%1: Updating View...", Binding_Name);
		
		// Selected_Item handler
		if (Selected_Item != string.Empty && m_SelectedPropertyConverter) {
			m_SelectedPropertyConverter.GetFromController(m_Controller, Selected_Item, 0);
			m_WidgetController.SetSelection(m_SelectedPropertyConverter);
		}
		
		if (m_PropertyType && m_PropertyConverter) {
			m_PropertyConverter.GetFromController(m_Controller, Binding_Name, 0);
			m_WidgetController.SetData(m_PropertyConverter);
		}
	}
	
	void UpdateModel()
	{
		if (!IsInitialized()) return;
		MVC.Trace("%1: Updating Model...", Binding_Name);
		
		// Selected_Item handler
		if (Selected_Item != string.Empty && m_SelectedPropertyConverter) {
			m_WidgetController.GetSelection(m_SelectedPropertyConverter);
			m_SelectedPropertyConverter.SetToController(m_Controller, Selected_Item, 0);
			m_Controller.NotifyPropertyChanged(Selected_Item);
		}
		
		if (m_PropertyType && m_PropertyConverter) {
			if (Two_Way_Binding && m_WidgetController && m_WidgetController.CanTwoWayBind()) {
				m_WidgetController.GetData(m_PropertyConverter);
				m_PropertyConverter.SetToController(m_Controller, Binding_Name, 0);
				m_Controller.NotifyPropertyChanged(Binding_Name);
			} else {
				m_Controller.NotifyPropertyChanged(Binding_Name);
			}
		}
	}
	
		
	override ScriptedViewBase GetParent() {
		return GetController();
	}
	
	// RoutedUICommand interfaces
	override bool OnClick(Widget w, int x, int y, int button)
	{
		MVC.Trace("ViewBinding::OnClick");
		UpdateModel();
		if (Relay_Command != string.Empty || m_RoutedUICommand) {
			
			switch (w.Type()) {
				case ButtonWidget: {
					InvokeCommand(new ButtonCommandArgs(ButtonWidget.Cast(w), button, ButtonWidget.Cast(w).GetState()));
					return true;
				}
			}
		}
			
		return super.OnClick(w, x, y, button);
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{	
		MVC.Trace("ViewBinding::OnChange");
		UpdateModel();
		if (Relay_Command != string.Empty || m_RoutedUICommand) {
			
			switch (w.Type()) {
				
				case CheckBoxWidget: {
					InvokeCommand(new CheckBoxCommandArgs(CheckBoxWidget.Cast(w), CheckBoxWidget.Cast(w).IsChecked()));
					return true;
				}
				
				case XComboBoxWidget: {
					InvokeCommand(new XComboBoxCommandArgs(XComboBoxWidget.Cast(w), XComboBoxWidget.Cast(w).GetCurrentItem()));
					return true;
				}
			}
		}
		
		return super.OnChange(w, x, y, finished);
	}
	
		
	void InvokeCommand(Param params)
	{
		MVC.Trace("ViewBinding::InvokeCommand");
		
		if (m_RoutedUICommand) {
			CanExecuteEventArgs e();
			m_RoutedUICommand.CanExecute.Invoke(this, e);
			if (e.CanExecute) {
				m_RoutedUICommand.Execute.Invoke(new RoutedUICommandArgs(this, params));
			}			
		}
		
		else if (m_Controller) {
			g_Script.CallFunction(m_Controller, Relay_Command, null, params);
		}
	}
	
	RoutedUICommand SetRoutedUICommand(string relay_command) 
	{
		MVC.Trace("ViewBinding: SetRoutedUICommand %1", relay_command);
		Relay_Command = relay_command;
		
		if (m_Controller && m_Controller.GetParent()) {
			m_RoutedUICommand = ScriptView.Cast(m_Controller.GetParent()).GetCommandManager().Get(Relay_Command);
			return m_RoutedUICommand;
		} else {
			MVC.Error("ViewBinding: Routed Commands only work with ScriptView!");
		}
		
		return null;
	}
	
	RoutedUICommand SetRoutedUICommand(RoutedUICommand relay_command)
	{
		MVC.Trace("ViewBinding: SetRoutedUICommand %1", relay_command.Type().ToString());
		m_RoutedUICommand = relay_command;
		return m_RoutedUICommand;
	}
}


