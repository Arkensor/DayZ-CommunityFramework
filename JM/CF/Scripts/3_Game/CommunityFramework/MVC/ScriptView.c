
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

class ScriptViewBase: ScriptedViewBase
{
	protected ref Controller m_ControllerInstance;
	void ScriptViewBase(Widget parent = null)
	{
		Trace("ScriptViewBase");
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
		
		LoadViewProperties(this, PropertyTypeHashMap.FromType(Type()), m_LayoutRoot);

		m_LayoutRoot.GetScript(m_ControllerInstance);
		
		// If no Controller is specified in the WB Root
		if (!m_ControllerInstance || !m_ControllerInstance.IsInherited(Controller)) {
			
			Log("Controller not found on %1, creating...", m_LayoutRoot.GetName());
			if (!GetControllerType().IsInherited(Controller)) {
				Error("%1 is invalid. Must inherit from Controller!", GetControllerType().ToString());
				return;
			}
			
			Class.CastTo(m_ControllerInstance, GetControllerType().Spawn());
			
			if (!m_ControllerInstance) {
				Error("Could not create Controller %1", GetControllerType().ToString());
				return;
			}
			
			// Since its not loaded in the WB, needs to be called here
			LoadViewProperties(m_ControllerInstance, PropertyTypeHashMap.FromType(GetControllerType()), m_LayoutRoot);
			m_ControllerInstance.OnWidgetScriptInit(m_LayoutRoot);
		}
	
		m_ControllerInstance.Debug_Logging = Debug_Logging;
		m_ControllerInstance.SetParent(this);
		//m_LayoutRoot.SetHandler(this);
	}

	void ~ScriptViewBase()
	{
		delete m_ControllerInstance;
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
		m_ControllerInstance = controller;
		m_ControllerInstance.Debug_Logging = Debug_Logging;
		m_ControllerInstance.OnWidgetScriptInit(m_LayoutRoot);
		m_ControllerInstance.SetParent(this);
	}	
	
	// Virtual Methods
	protected string GetLayoutFile();
	
	protected typename GetControllerType() {
		return Controller;
	}
}

class ScriptView: ScriptViewBase
{
	protected Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}
	
	void ScriptView(Widget parent = null)
	{
		EnScript.GetClassVar(this, "m_ControllerInstance", 0, m_Controller);
	}
}




