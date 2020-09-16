


class ViewBinding: ScriptedWidgetEventHandler
{
	// Layout root - CANNOT be null
	protected Widget m_LayoutRoot;
	
	// Variable name to bind to. If blank, uses the Widget name (not advised)
	protected reference string Binding_Name;
		
	// Variable name to bind the Selected Item to
	// Only valid if type is ObservableCollection
	protected reference string Selected_Item;
	
	// If true, Bindings go both ways. Otherwise the controller is the master
	protected reference bool Two_Way_Binding;
	
	// Name of RelayCommand class that is controlled by ViewBinding
	// Can be either name of Class that inherits from RelayCommand, OR a function within the controller
	protected reference string Relay_Command;

	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	string GetBindingName() { 
		return Binding_Name; 
	}
	
	string GetRelayCommand() {
		return Relay_Command;
	}

	typename GetPropertyType(string property_name) {
		return m_Controller.GetPropertyType(property_name);
	}
	
	// Weak reference to Parent controller	
	protected autoptr Controller m_Controller;
	
	protected autoptr ref RelayCommand 		m_RelayCommand;
	protected autoptr ref TypeConverter 	m_PropertyDataConverter;
	protected autoptr ref WidgetController 	m_WidgetController;
	protected autoptr ref TypeConverter 	m_SelectedDataConverter;
	
	private bool m_IsInitialized;
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
		MVC.Trace("ViewBinding::OnWidgetScriptInit %1", m_LayoutRoot.GetName());
		
		if (!m_LayoutRoot) {
			MVC.Error("ViewBinding: Layout was null!");
		}
		
		if (Binding_Name == string.Empty) {
			Binding_Name = m_LayoutRoot.GetName();
		}
		
		if (Relay_Command != string.Empty) {
			
			if (!Relay_Command.ToType()) {
				MVC.Log("ViewBinding: Type not found: %1 - Assuming it is function on Controller", Relay_Command);
			} else if (!Relay_Command.ToType().IsInherited(RelayCommand)) {
				MVC.Error("ViewBinding: %1 must inherit from RelayCommand", Relay_Command);
				return;
			} else {
				m_RelayCommand = Relay_Command.ToType().Spawn();
			}
		}
		
		m_WidgetController = MVC.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController) {
			MVC.UnsupportedTypeError(m_LayoutRoot.Type());
		}
		
		// Check for two way binding support
		if (Two_Way_Binding && !m_WidgetController.CanTwoWayBind()) {
			MVC.Error(string.Format("Two Way Binding for %1 is not supported!", m_LayoutRoot.Type().ToString()));
		}
		
		m_IsInitialized = true;
	}
	
	void SetController(Controller controller) 
	{ 
		//GetLogger().Log("ViewBinding::SetController: %1", controller.GetLayoutRoot().GetName());
		m_Controller = controller;
	
		if (!m_Controller) {
			MVC.Error("ViewBinding::SetController: Controller is null!");
			return;
		}
		
		if (!GetPropertyType(Binding_Name)) {
			MVC.PropertyNotFoundError(Binding_Name);
		}

		if (Selected_Item != string.Empty)
			m_SelectedDataConverter = MVC.GetTypeConversion(GetPropertyType(Selected_Item));
				
		if (GetPropertyType(Binding_Name).IsInherited(Observable)) {
			m_PropertyDataConverter = MVC.GetTypeConversion(Observable.Cast(GetPropertyType(Binding_Name).Spawn()).GetType());
		} else {
			m_PropertyDataConverter = MVC.GetTypeConversion(GetPropertyType(Binding_Name));
		}
		
		// Updates the view on first load
		UpdateView();
	}
	
	void OnPropertyChanged()
	{
		//GetLogger().Log(string.Format("ViewBinding::OnPropertyChanged: %1", Binding_Name), "JM_CF_MVC");
		UpdateView();
	}

	void OnCollectionChanged(ref CollectionChangedEventArgs args)
	{
		//GetLogger().Log(string.Format("ViewBinding::OnCollectionChanged: %1", Binding_Name), "JM_CF_MVC");

		if (!m_PropertyDataConverter) {
			MVC.TypeConversionError(GetPropertyType(Binding_Name));
			return;			
		}
		
		if (!m_WidgetController) {
			MVC.UnsupportedTypeError(m_LayoutRoot.Type());
			return;
		}

		//PrintFormat("Updating Collection View: %1", m_LayoutRoot.Type().ToString());
			
		// Anonymouse Data Setter
		m_PropertyDataConverter.SetParam(args.param4);
		switch (args.param2) {
						
			case NotifyCollectionChangedAction.Add: {
				m_WidgetController.InsertData(args.param3, m_PropertyDataConverter);
				break;
			}
			
			case NotifyCollectionChangedAction.Remove: {
				m_WidgetController.RemoveData(args.param3, m_PropertyDataConverter);
				break;
			}
			
			case NotifyCollectionChangedAction.Set: {
				m_WidgetController.ReplaceData(args.param3, m_PropertyDataConverter);
				break;
			}
			
			case NotifyCollectionChangedAction.Move: {
				// this ones a weird case /shrug
				m_WidgetController.MoveData(args.param3, Param1<int>.Cast(args.param4).param1);
				break;	
			}
			
			case NotifyCollectionChangedAction.Clear: {
				m_WidgetController.ClearData();
				break;
			}
		}
	}
	

	
	private void UpdateView()
	{
		//GetLogger().Log("ViewBinding::UpdateView", "JM_CF_MVC");
		if (!m_Controller || !m_IsInitialized) return;
		
		if (!m_PropertyDataConverter) {	
			m_PropertyDataConverter = MVC.GetTypeConversion(GetPropertyType(Binding_Name));
			if (!m_PropertyDataConverter) {
				MVC.TypeConversionError(GetPropertyType(Binding_Name));
				return;
			}
		}
		
		if (m_SelectedDataConverter) {
			m_SelectedDataConverter.GetFromController(m_Controller, Selected_Item, 0);
			m_WidgetController.SetSelection(m_SelectedDataConverter);
		}

		m_PropertyDataConverter.GetFromController(m_Controller, Binding_Name, 0);
		m_WidgetController.SetData(m_PropertyDataConverter);
	}
	
	private void UpdateModel()
	{
		//GetLogger().Log("ViewBinding::UpdateModel", "JM_CF_MVC");
		if (!m_Controller || !m_IsInitialized) return;
		
		if (!m_PropertyDataConverter) {	
			m_PropertyDataConverter = MVC.GetTypeConversion(GetPropertyType(Binding_Name));
			if (!m_PropertyDataConverter) {
				MVC.TypeConversionError(GetPropertyType(Binding_Name));
				return;
			}
		}
		
		if (m_SelectedDataConverter) {
			m_WidgetController.GetSelection(m_SelectedDataConverter);
			m_SelectedDataConverter.SetToController(m_Controller, Selected_Item, 0);
			m_Controller.NotifyPropertyChanged(Selected_Item);
		}
		
		if (!Two_Way_Binding || !m_WidgetController.CanTwoWayBind()) {
			m_Controller.NotifyPropertyChanged(Binding_Name);
			return;
		}

				
		m_WidgetController.GetData(m_PropertyDataConverter);
		m_PropertyDataConverter.SetToController(m_Controller, Binding_Name, 0);
		m_Controller.NotifyPropertyChanged(Binding_Name);
	}
	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		//GetLogger().Log("ViewBinding::OnClick " + w.Type());
		
		switch (w.Type()) {
			case ButtonWidget: {
				UpdateModel();
				InvokeCommand(new ButtonCommandArgs(ButtonWidget.Cast(w), button, ButtonWidget.Cast(w).GetState()));
				break;
			}
		}
		
		return false;
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		//GetLogger().Log("ViewBinding::OnChange " + w.GetName());
	
		switch (w.Type()) {
			
			case CheckBoxWidget: {
				InvokeCommand(new CheckBoxCommandArgs(CheckBoxWidget.Cast(w), CheckBoxWidget.Cast(w).IsChecked()));
				break;
			}
			
			case XComboBoxWidget: {
				InvokeCommand(new XComboBoxCommandArgs(XComboBoxWidget.Cast(w), XComboBoxWidget.Cast(w).GetCurrentItem()));
				break;
			}
		}

		UpdateModel();		
		return false;
	}
	
	
		
	void InvokeCommand(Param params)
	{
		MVC.Trace("ViewBinding::InvokeCommand");
		
		if (!m_IsInitialized) return;
		
		if (!m_RelayCommand && m_Controller) {
			g_Script.CallFunction(m_Controller, Relay_Command, null, params);
			return;
		}
		
		if (m_RelayCommand.CanExecute()) {
			m_RelayCommand.Execute(new RelayCommandArgs(this, params));
		}
	}
	
	void UpdateCommand()
	{
		/*
		if (Command_CanExecute == string.Empty) {
			return;
		}
		
		//GetLogger().Log("ViewBinding::UpdateCommand", "JM_CF_MVC");
		
		bool result;
		if (g_Script.CallFunction(m_Controller, Command_CanExecute, result, 0) != 0) {
			return;
		}
		
		if (result) {
			m_LayoutRoot.ClearFlags(WidgetFlags.IGNOREPOINTER);
		} else {
			m_LayoutRoot.SetFlags(WidgetFlags.IGNOREPOINTER);
			if (GetFocus() == m_LayoutRoot) {
				SetFocus(null);
			}
		}*/
	}
}


