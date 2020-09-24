
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
	
	void ScriptView(Widget parent = null)
	{
		Trace("ScriptView");
		WorkspaceWidget workspace = GetWorkbenchGame().GetWorkspace();
		if (!workspace) {
			Error("Workspace was null, try reloading Workbench");
			return;
		} 

		if (!GetLayoutFile()) {
			Error("Layout file not found! Are you overriding GetLayoutFile?");
			return;
		}
		
		Log("Loading %1", GetLayoutFile());
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), parent);
		if (!m_LayoutRoot) {
			Error("Invalid layout file %1", GetLayoutFile());
			return;
		}
				
		if (GetControllerType()) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller || !GetControllerType().IsInherited(Controller)) {
				Error("ScriptView: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.Debug_Logging = Debug_Logging;
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		}
		
		PropertyTypeHashMap property_map = PropertyTypeHashMap.FromType(Type());
		//property_map.RemoveType(ScriptView); crashing ?
		foreach (string property_name, typename property_type: property_map) {
			
			if (property_type.IsInherited(Widget)) {
				Widget target = m_LayoutRoot.FindAnyWidget(property_name);
				
				// Allows for LayoutRoot to be referenced as well
				if (!target && m_LayoutRoot.GetName() == property_name) {
					target = m_LayoutRoot;
				}
	
				EnScript.SetClassVar(this, property_name, 0, target);
			}
		}
	}
	

	void ~ScriptView()
	{
		Trace("~ScriptView");
		delete m_Controller;
	}

					
	// Abstract Methods
	protected string GetLayoutFile();
	protected typename GetControllerType();
}




