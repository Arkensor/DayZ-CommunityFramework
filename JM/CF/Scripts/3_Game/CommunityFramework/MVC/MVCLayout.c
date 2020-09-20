
// Abstract Class
// Inherit from this if you want to create UI elements with 100% script
/*

Example:

class CustomDialogWindow: MVCLayout
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

class MVCLayout: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	protected ref Controller m_Controller;
	
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	Controller GetController() {
		return m_Controller;
	}
	
	void MVCLayout(Widget parent = null)
	{
		MVC.Trace("MVCLayout");
		if (!GetLayoutFile()) {
			MVC.Error("MVCLayout: You must override GetLayoutFile with the .layout file path");
			return;
		}		
		
		MVC.Log("MVCLayout: Loading %1", GetLayoutFile());
		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
				
		if (!workspace) {
			MVC.Error("MVCLayout: Workspace was null, try reloading Workbench");
			return;
		}
		
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), parent);
		if (!m_LayoutRoot) {
			MVC.Error("MVCLayout: Invalid layout file %1", GetLayoutFile());
			return;
		}
		
		PropertyTypeHashMap property_map = PropertyTypeHashMap.FromType(Type());
		property_map.RemoveType(MVCLayout);
		
		int property_count;
		foreach (string property_name, typename property_type: property_map) {
			
			Widget target = m_LayoutRoot.FindAnyWidget(property_name);
			
			// Allows for LayoutRoot to be referenced as well
			if (!target && m_LayoutRoot.GetName() == property_name) {
				target = m_LayoutRoot;
			}

			EnScript.SetClassVar(this, property_name, 0, target);
			property_count++;
		}
		
		
		MVC.Log("MVCLayout: %1 properties found!", property_count.ToString());
		if (GetControllerType()) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller) {
				MVC.Error("MVCLayout: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);
			m_LayoutRoot.SetHandler(this);
		}
	}
	
	void ~MVCLayout() 
	{
		MVC.Trace("~MVCLayout");
		m_LayoutRoot.Unlink();
		delete m_Controller;
	}
	
			
	// Abstract Methods
	protected string GetLayoutFile();
	protected typename GetControllerType();	

}