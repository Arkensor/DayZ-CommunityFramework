
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
	
	// Virtual Methods
	protected string GetLayoutFile();
}

class ScriptViewTemplate<Class T>: ScriptViewBase
{
	protected ref T m_Controller;
	T GetController() {
		return m_Controller;
	}
	
	void ScriptViewTemplate(Widget parent = null)
	{
		m_LayoutRoot.GetScript(m_Controller);
		
		// If no Controller is specified in the WB Root
		if (!m_Controller || !m_Controller.IsInherited(Controller)) {

			if (!T.IsInherited(Controller)) {
				Error("%1 is invalid. Must inherit from Controller!", T.ToString());
				return;
			}
			
			Class.CastTo(m_Controller, T.Spawn());
			
			if (!m_Controller) {
				Error("Could not create Controller %1", T.ToString());
				return;
			}
			
			// Since its not loaded in the WB, needs to be called here
			LoadViewProperties(m_Controller, PropertyTypeHashMap.FromType(T), m_LayoutRoot);
		}
	
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		m_Controller.SetParent(this);
		//m_LayoutRoot.SetHandler(this);
	}
	
	void ~ScriptViewTemplate()
	{
		Trace("~ScriptViewTemplate");
		delete m_Controller;
	}
	
	// Useful if you want to set to an existing controller
	void SetController(T controller)
	{
		m_Controller = controller;
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		m_Controller.SetParent(this);
	}	
}


class ScriptView: ScriptViewBase
{		
	protected ref Controller m_Controller;
	Controller GetController() {
		return m_Controller;
	}
	
	void ScriptView(Widget parent = null)
	{
		m_LayoutRoot.GetScript(m_Controller);
		
		// If no Controller is specified in the WB Root
		if (!m_Controller || !m_Controller.IsInherited(Controller)) {

			if (!GetControllerType().IsInherited(Controller)) {
				Error("%1 is invalid. Must inherit from Controller!", GetControllerType().ToString());
				return;
			}
			
			Class.CastTo(m_Controller, GetControllerType().Spawn());
			
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
	}
	
	void ~ScriptView()
	{
		Trace("~ScriptView");
		delete m_Controller;
	}
	
	// Useful if you want to set to an existing controller
	void SetController(Controller controller)
	{
		m_Controller = controller;
		m_Controller.Debug_Logging = Debug_Logging;
		m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		m_Controller.SetParent(this);
	}		

	protected typename GetControllerType() {
		return Controller;
	}
}




