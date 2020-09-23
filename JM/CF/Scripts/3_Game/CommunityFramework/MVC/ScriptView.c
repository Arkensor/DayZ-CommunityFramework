
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
	protected ScriptView m_ParentView;
	
	// Weak reference to child controllers
	protected ref set<Controller> m_Controllers = new set<Controller>();
	
	// Hashmap of all relay commands in the ScriptView
	protected ref RelayCommandHashMap m_RelayCommandHashMap = new RelayCommandHashMap();

	
	void ScriptView(ScriptView parent = null)
	{
		MVC.Trace("ScriptView");
		m_ParentView = parent;
		

				
		if (!GetLayoutFile()) {
			MVC.Error("ScriptView: You must override GetLayoutFile with the .layout file path");
			return;
		}
		
		MVC.Log("ScriptView: Loading %1", GetLayoutFile());
		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
		if (!workspace) {
			MVC.Error("ScriptView: Workspace was null, try reloading Workbench");
			return;
		}
		
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), m_ParentView.GetLayoutRoot());
		if (!m_LayoutRoot) {
			MVC.Error("ScriptView: Invalid layout file %1", GetLayoutFile());
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
				// todo can i check to see if initializing it after the constructor works? like a pointer
				// cant now
				m_RelayCommandHashMap.Insert(property_name, command);				
			}
		}
		
		
		
		// Find a way to enumerate all controllers in a layout file
		
		/*
		// Has to be called before other views are created
		//m_LayoutRoot.SetHandler(this);
		// You can keep the controller in scriptclass if you want, to keep reactive UI's up
		m_LayoutRoot.GetScript(m_Controller);
		
		if (!m_Controller && GetControllerType().IsInherited(Controller)) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller) {
				MVC.Error("ScriptView: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);	
		}
		
		m_Controller.SetScriptView(this);*/
		
	}
	
	void ~ScriptView() 
	{
		MVC.Trace("~ScriptView");
		m_LayoutRoot.Unlink();
		delete m_Controllers;
		delete m_RelayCommandHashMap;
	}

	void OnWidgetScriptInit(Widget w)
	{
		// Extra safety measure
#ifdef COMPONENT_SYSTEM
		MVC.Error("ScriptView should NOT be called in the Workbench Script Class!");
		return;
#endif
	}
					
	// Abstract Methods
	protected string GetLayoutFile();
	
	protected typename GetControllerType() {
		return Controller;
	}
}
