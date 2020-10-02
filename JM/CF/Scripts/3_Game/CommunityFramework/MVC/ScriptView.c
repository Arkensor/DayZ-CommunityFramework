
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
	protected ref Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}
		
	void ScriptView(Widget parent = null)
	{
		//Debug_Logging = true;
		Trace("ScriptView");
		if (!GetLayoutFile()) {
			Error("Layout file not found! Are you overriding GetLayoutFile?");
			return;
		}
		
		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
		if (!workspace) {
			Error("Workspace was null, try reloading Workbench");
			return;
		}
		
		Log("Loading %1", GetLayoutFile());
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), parent);
		if (!m_LayoutRoot) {
			Error("Invalid layout file %1", GetLayoutFile());
			return;
		}
		
		m_LayoutRoot.GetScript(m_Controller);
		
		// If no Controller is specified in the WB Root
		if (!m_Controller || !m_Controller.IsInherited(Controller)) {

			if (!GetControllerType().IsInherited(Controller)) {
				Error("%1 is invalid. Must inherit from Controller!", GetControllerType().ToString());
				return;
			}
			
			m_Controller = GetControllerType().Spawn();
			
			if (!m_Controller) {
				Error("Could not create Controller %1", GetControllerType().ToString());
				return;
			}
			
			// Since its not loaded in the WB, needs to be called here
			LoadViewProperties(m_Controller, PropertyTypeHashMap.FromType(GetControllerType()), m_LayoutRoot);
		}
	
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		m_Controller.SetParent(this);
		//m_LayoutRoot.SetHandler(this);
	
		LoadViewProperties(this, PropertyTypeHashMap.FromType(Type()), m_LayoutRoot);
	}
	

	void ~ScriptView()
	{
		Trace("~ScriptView");
		delete m_Controller;
	}
	
	void SetParent(Widget parent)
	{
		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
		if (!workspace) {
			Error("Workspace was null, try reloading Workbench");
			return;
		}
		
		if (m_LayoutRoot && m_LayoutRoot.GetParent()) {
			m_LayoutRoot.Unlink();
		}
		
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), parent);
	}
		
	// Useful if you want to set to an existing controller
	void SetController(Controller controller)
	{
		m_Controller = controller;
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		m_Controller.SetParent(this);
	}
	
		
	// Abstract Methods
	protected string GetLayoutFile();
	protected typename GetControllerType() {
		return Controller;
	}
}




