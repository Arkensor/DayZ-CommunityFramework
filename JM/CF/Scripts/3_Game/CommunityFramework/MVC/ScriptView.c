
// Abstract Class
// Inherit from this if you want to create UI elements with 100% script
/*

Example:

class CustomDialogWindow: ScriptView
{
	override string GetLayoutFile() {
		return "MyMod/gui/Layouts/dialogs/Dialog.layout";
	}
}

	CustomDialogWindow window = new CustomDialogWindow();
	window.Show();
	....
	....
	window.Close();

*/

class ScriptView: ScriptedViewBase
{
	// Weak reference to controller
	protected ref Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}
	
	// Hashmap of all relay commands in the ScriptView
	protected autoptr RelayCommandHashMap m_RelayCommandHashMap = new RelayCommandHashMap();
	
	
#ifndef COMPONENT_SYSTEM
	
	private void ScriptView(Widget parent)
	{
		Trace("ScriptView");
			
		if (!GetLayoutFile()) {
			Error("You must override GetLayoutFile with the .layout file path");
			return;
		}

		Log("Loading %1", GetLayoutFile());

		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
		if (!workspace) {
			Error("Workspace was null, try reloading Workbench");
			return;
		}
		
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), parent);
		if (!m_LayoutRoot) {
			Error("Invalid layout file %1", GetLayoutFile());
			return;
		}
		
		m_LayoutRoot.SetHandler(this);
		
		PropertyTypeHashMap property_map = PropertyTypeHashMap.FromType(Type());
		property_map.RemoveType(ScriptView);
		foreach (string property_name, typename property_type: property_map) {
			
			if (property_type.IsInherited(Widget)) {
				Widget target = m_LayoutRoot.FindAnyWidget(property_name);
				
				// Allows for LayoutRoot to be referenced as well
				if (!target && m_LayoutRoot.GetName() == property_name) {
					target = m_LayoutRoot;
				}
	
				EnScript.SetClassVar(this, property_name, 0, target);
			}
			/*
			else if (property_type.IsInherited(RelayCommand)) {
				
				RelayCommand command;
				EnScript.GetClassVar(this, property_name, 0, command);
				m_RelayCommandHashMap.Insert(property_name, command);				
			}*/
		}
		
		
		
		if (!m_Controller && GetControllerType().IsInherited(Controller)) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller) {
				Error("ScriptView: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);	
		}
		
		ViewBindingHashMap data_bindings = m_Controller.GetViewBindings();
		Print(data_bindings.Count());
		foreach (Widget widget, ViewBinding view_binding: data_bindings) {
			if (view_binding.Relay_Command != string.Empty) {
				typename relay_command = property_map.Get(view_binding.Relay_Command);
				if (relay_command) {
					view_binding.SetRelayCommand(relay_command.Spawn());
					Print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
				}
			}
		}
	}
	
	static ScriptView Create()
	{
		ScriptView script_view = new ScriptView(null);
		return script_view;
	}
	
	static ScriptView Create(Widget parent)
	{
		ScriptView script_view = new ScriptView(parent);
		
		return script_view;
	}
	
	static ScriptView Create(ScriptView parent)
	{	
		ScriptView script_view = new ScriptView(parent.GetLayoutRoot());
		
		return script_view;
	}
	
	void ~ScriptView() 
	{
		delete m_Controller;
		m_LayoutRoot.Unlink();
	}
		
#else
	
	private void ScriptView()
	{
		

	}
	
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		
		if (!GetControllerType()) {
			Error("Controller not found! Are you overriding GetControllerType?");
			return;
		}
		
		if (!GetLayoutFile()) {
			Error("Layout file not found! Are you overriding GetLayoutFile?");
			return;
		}
				
		
		m_Controller = GetControllerType().Spawn();
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(w);
		
		PropertyTypeHashMap property_map = PropertyTypeHashMap.FromType(Type());
		property_map.RemoveType(ScriptView);
		foreach (string property_name, typename property_type: property_map) {
			
			if (property_type.IsInherited(Widget)) {
				Widget target = m_LayoutRoot.FindAnyWidget(property_name);
				
				// Allows for LayoutRoot to be referenced as well
				if (!target && m_LayoutRoot.GetName() == property_name) {
					target = m_LayoutRoot;
				}
	
				EnScript.SetClassVar(this, property_name, 0, target);
			}
			/*
			else if (property_type.IsInherited(RelayCommand)) {
				
				RelayCommand command;
				EnScript.GetClassVar(this, property_name, 0, command);
				m_RelayCommandHashMap.Insert(property_name, command);				
			}*/
		}
		
		ViewBindingHashMap data_bindings = m_Controller.GetViewBindings();
		if (data_bindings) {
			foreach (Widget widget, ViewBinding view_binding: data_bindings) {
				if (view_binding.Relay_Command != string.Empty) {
					typename relay_command = property_map.Get(view_binding.Relay_Command);
					if (relay_command) {
						RelayCommand command = relay_command.Spawn();
						view_binding.SetRelayCommand(command);
						command.SetScriptView(this);
					}
				}
			}
		}
	}
	
	
#endif
					
	// Abstract Methods
	protected string GetLayoutFile();
	protected typename GetControllerType();
}
