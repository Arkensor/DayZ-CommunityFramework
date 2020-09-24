

class ViewBinding: ScriptedViewBase
{	
	// Name of Variable to bind to
	reference string Binding_Name;	
			
	// Name of Variable to bind "selected item" to...
	// Only valid if type is ObservableCollection
	reference string Selected_Item;
	
	// If true, Bindings go both ways. Otherwise the controller is the master
	reference bool Two_Way_Binding;
	
	// Name of RelayCommand class that is controlled by ViewBinding
	reference string Relay_Command;
	
	// Weak reference to Relay Command
	protected RelayCommand m_RelayCommand;
	void SetRelayCommand(RelayCommand relay_command) {
		m_RelayCommand = relay_command;
	}

	// Weak reference to Parent controller	
	protected Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}
		
	protected autoptr ref TypeConverter m_PropertyConverter;
	protected autoptr ref TypeConverter m_SelectedConverter;
	
	protected autoptr ref WidgetController m_WidgetController;
	

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		
		m_WidgetController = MVC.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController) {
			Error("Could not find WidgetController for type %1\nOverride MVC.RegisterWidgetControllers to register custom WidgetControllers", m_LayoutRoot.GetTypeName());
			return;
		}
		
		// Check for two way binding support
		if (Two_Way_Binding && !m_WidgetController.CanTwoWayBind()) {
			Log("Two Way Binding for %1 is not supported!", m_LayoutRoot.Type().ToString());
		}
	}
	
	void SetProperties(typename binding_type, typename selected_type)
	{
		Trace("SetProperties");
		// Were not trying to data bind to empty Binding_Name
		if (binding_type && Binding_Name != string.Empty) {
			m_PropertyConverter = MVC.GetTypeConversion(binding_type);
			if (!m_PropertyConverter) {
				Error("Could not find TypeConverter for type %1 in Binding_Name\nMod MVC.RegisterConversionTemplates to register custom TypeConverters", binding_type.ToString());
			}
		}
		
		// Were not trying to data bind to empty Selected_Item
		if (selected_type && Selected_Item != string.Empty) {
			m_SelectedConverter = MVC.GetTypeConversion(selected_type);
			if (!m_SelectedConverter) {
				Error("Could not find TypeConverter for type %1 in Selected_Item\nMod MVC.RegisterConversionTemplates to register custom TypeConverters", selected_type.ToString());
			}
		}
	}

	// Controller -> view
	void UpdateView(Controller controller)
	{
		Trace("UpdateView");
		Log("Updating View %1...", Binding_Name);
		if (!m_WidgetController) return;

		// Binding_Name handler
		if (m_PropertyConverter) {
			m_PropertyConverter.GetFromController(controller, Binding_Name, 0);
			m_WidgetController.SetData(m_PropertyConverter);
		}
		
		// Selected_Item handler
		if (m_SelectedConverter) {
			m_SelectedConverter.GetFromController(controller, Selected_Item, 0);
			m_WidgetController.SetSelection(m_SelectedConverter);
		}
	}
	
	// View -> Controller
	void UpdateModel(Controller controller)
	{
		Trace("UpdateModel");
		
		Log("Updating Model %1...", Binding_Name);
		if (!m_WidgetController) return;
		
		// Binding_Name handler
		if (m_PropertyConverter && Two_Way_Binding && m_WidgetController.CanTwoWayBind()) {
			m_WidgetController.GetData(m_PropertyConverter);
			m_PropertyConverter.SetToController(controller, Binding_Name, 0);
			//NotifyPropertyChanged(); maybe?
		}
		
		// Selected_Item handler
		if (m_SelectedConverter) {
			m_WidgetController.GetSelection(m_SelectedConverter);
			m_SelectedConverter.SetToController(controller, Selected_Item, 0);
			//NotifyPropertyChanged(); maybe?
		}		
	}	
		
	void InvokeCommand(Param params)
	{
		Trace("InvokeCommand");
		
		if (m_RelayCommand) {
			CanExecuteEventArgs e();
			if (m_RelayCommand.CanExecute()) {
				m_RelayCommand.Execute(new RelayCommandArgs(this, params));
			}
		}
		
		else if (m_Controller) {
			g_Script.CallFunction(m_Controller, Relay_Command, null, params);
		}
	}
	
	void OnCollectionChanged(ref CollectionChangedEventArgs args)
	{
		Trace("OnCollectionChanged");
		
		Log("Updating Collection View: %1", m_LayoutRoot.Type().ToString());
		if (!m_WidgetController) return;

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
}


