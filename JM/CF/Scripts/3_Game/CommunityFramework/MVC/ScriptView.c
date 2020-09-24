
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
			else if (property_type.IsInherited(RelayCommand)) {
				
				RelayCommand command;
				EnScript.GetClassVar(this, property_name, 0, command);
				m_RelayCommandHashMap.Insert(property_name, command);				
			}
		}
		
		
		// Has to be called before other views are created
		m_LayoutRoot.SetHandler(this);
		if (!m_Controller && GetControllerType().IsInherited(Controller)) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller) {
				Error("ScriptView: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);	
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
	}
	
	
#endif
					
	// Abstract Methods
	protected string GetLayoutFile();
	protected typename GetControllerType();
}
