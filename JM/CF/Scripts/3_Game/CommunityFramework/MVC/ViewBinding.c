


class ViewBinding: MVCEventHandler
{
	
	// Name of Binding. If blank, uses the Widget name (not advised)
	protected reference string Binding_Name;
	
	// Index of Binding
	protected reference int Binding_Index;
	
	// Function called when type is Clicked, Selected, or Changed
	protected reference string Command_Execute;
	
	// Function that returns bool defining whether or not the Command_Execute can be called
	protected reference string Command_CanExecute;
	
	// Only valid if type is ObservableCollection
	protected reference string Selected_Item;
	
	// If true, Bindings go both ways. Otherwise the controller is the master
	protected reference bool Two_Way_Binding;
	
	
	Widget GetRoot() { 
		return m_LayoutRoot; 
	}
	
	string GetBindingName() { 
		return Binding_Name; 
	}

	
	typename GetPropertyType(string property_name) {
		return m_Controller.GetPropertyType(property_name);
	}
	

	
	protected Controller m_Controller;
	protected ref TypeConverter m_PropertyDataConverter;
	protected ref WidgetController m_WidgetController;
	
	protected ref TypeConverter m_SelectedDataConverter;
	
	void ViewBinding() { /*GetLogger().Log("ViewBinding");*/ }
	void ~ViewBinding() { /*GetLogger().Log("~ViewBinding");*/ }
	
	void SetController(Controller controller) 
	{ 
		GetLogger().Log("ViewBinding::SetController: %1", controller.GetLayoutRoot().GetName());
		m_Controller = controller;
	
		
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
	
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		GetLogger().Log("[%1] ViewBinding::Init", w.GetName());
		
		if (Binding_Name == string.Empty) {
			Binding_Name = m_LayoutRoot.GetName();
		}
		
		m_WidgetController = MVC.GetWidgetController(m_LayoutRoot);
		if (!m_WidgetController) {
			MVC.UnsupportedTypeError(m_LayoutRoot.Type());
		}
		
		// Check for two way binding support
		if (Two_Way_Binding && !m_WidgetController.CanTwoWayBind()) {
			EditorLog.Error("Two Way Binding for %1 is not supported!", m_LayoutRoot.Type().ToString());
		}
	}
	
	void OnPropertyChanged()
	{
		GetLogger().Log("ViewBinding::OnPropertyChanged: %1", Binding_Name);
		UpdateView();
	}

	void OnCollectionChanged(ref CollectionChangedEventArgs args)
	{
		GetLogger().Log("ViewBinding::OnCollectionChanged: %1", Binding_Name);

		
		if (!m_PropertyDataConverter) {
			MVC.TypeConversionError(GetPropertyType(Binding_Name));
			return;			
		}
		
		if (!m_WidgetController) {
			MVC.UnsupportedTypeError(m_LayoutRoot.Type());
			return;
		}

		EditorLog.Debug("Updating Collection View: %1", m_LayoutRoot.Type().ToString());
			
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
		GetLogger().Log("ViewBinding::UpdateView", "JM_CF_MVC");

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

		m_PropertyDataConverter.GetFromController(m_Controller, Binding_Name, Binding_Index);
		m_WidgetController.SetData(m_PropertyDataConverter);
	}
	
	private void UpdateModel()
	{
		GetLogger().Log("ViewBinding::UpdateModel", "JM_CF_MVC");
		
		
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
		//return super.OnChange(w, x, y, finished);
	}
	
	
	
	override void MVCOnMouseDown(Widget target, int button, int x, int y)
		m_Controller.MVCOnMouseDown(target, button, x, y);
	
	override void MVCOnMouseUp(Widget target, int button, int x, int y)
		m_Controller.MVCOnMouseUp(target, button, x, y);
	
	override void MVCOnMouseWheel(Widget target, int direction, int x, int y)
		m_Controller.MVCOnMouseWheel(target, direction, x, y);
	
	override void MVCOnClick(Widget target, int button, int x, int y)
		m_Controller.MVCOnClick(target, button, x, y);
	
	override void MVCOnDoubleClick(Widget target, int button, int x, int y)
		m_Controller.MVCOnDoubleClick(target, button, x, y);
	
//	override void MVCOnKeyPress(int key)
		//m_Controller.OnKeyPress(key);
	
	override void MVCOnMouseEnter(Widget target, int x, int y)
		m_Controller.MVCOnMouseEnter(target, x, y);
	
	override void MVCOnMouseLeave(Widget target, int x, int y)
		m_Controller.MVCOnMouseLeave(target, x, y);
	
	override void MVCOnDrag(Widget target, int x, int y) 
		m_Controller.MVCOnDrag(target, x, y);
	
	override void MVCOnDrop(Widget target, Widget drop_target, int x, int y)
		m_Controller.MVCOnDrop(target, drop_target, x, y);
	
	override void MVCOnDragging(Widget target, int x, int y)
		m_Controller.MVCOnDragging(target, x, y);
	
	override void MVCOnDropReceived(Widget target, Widget received_target, int x, int y)
		m_Controller.MVCOnDropReceived(target, received_target, x, y);
		
	
	void InvokeCommand(Param params)
	{
		if (Command_Execute == string.Empty) {
			return;
		}
				
		GetLogger().Log("ViewBinding::InvokeCommand", "JM_CF_MVC");
		g_Script.CallFunction(m_Controller, Command_Execute, null, params);
	}
	
	void UpdateCommand()
	{
		if (Command_CanExecute == string.Empty) {
			return;
		}
		
		GetLogger().Log("ViewBinding::UpdateCommand", "JM_CF_MVC");
		
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
		}
	}
}


