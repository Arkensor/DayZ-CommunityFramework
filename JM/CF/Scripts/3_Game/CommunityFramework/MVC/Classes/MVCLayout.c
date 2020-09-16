
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


*/
class MVCLayout
{
	protected Widget m_LayoutRoot;
	
	protected ref Controller m_Controller;
	protected ref PropertyHashMap m_PropertyHashMap = PropertyHashMap.FromType(Type());
	
	private ref ScriptInvoker m_UpdateQueue = GetGame().GetUpdateQueue(CALL_CATEGORY_GUI);
	
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	Controller GetController() {
		return m_Controller;
	}
	
	void MVCLayout()
	{
		MVC.Trace("MVCLayout");
		if (GetLayoutFile() == string.Empty) {
			MVC.Error("MVCLayout: You must override GetLayoutFile with the .layout file path");
			return;
		}		
		
		MVC.Log("MVCLayout: Loading %1", GetLayoutFile());
		WorkspaceWidget workspace = GetGame().GetWorkspace();
		if (!workspace) {
			MVC.Error("MVCLayout: Workspace was null, try reloading Workbench");
			return;
		}
		
		m_LayoutRoot = workspace.CreateWidgets(GetLayoutFile(), null);
		if (!m_LayoutRoot) {
			MVC.Error("MVCLayout: Invalid layout file!");
			return;
		}
		
		m_LayoutRoot.Show(false);
		
		int property_count = LoadWidgets();
		MVC.Log("MVCLayout: %1 properties found!", property_count.ToString());
		
		if (GetControllerType() != Controller) {
			m_Controller = GetControllerType().Spawn();
			if (!m_Controller) {
				MVC.Error("MVCLayout: Invalid Controller %1", GetControllerType().ToString());
				return;
			}
			
			m_Controller.OnWidgetScriptInit(m_LayoutRoot);
		}
	}
	
	void ~MVCLayout()
	{
		//MVC.Trace("~MVCLayout");
		if (m_UpdateQueue) {
			m_UpdateQueue.Remove(Update);
		}
	}
	
	int LoadWidgets()
	{
		int count;
		foreach (string property_name, typename property_type: m_PropertyHashMap) {
			Widget target = m_LayoutRoot.FindAnyWidget(property_name);
			
			// Allows for LayoutRoot to be referenced aswell
			if (!target && m_LayoutRoot.GetName() == property_name) {
				target = m_LayoutRoot;
			}
			
			if (target) {
				EnScript.SetClassVar(this, property_name, 0, target);
				count++;
			}
		}
		
		return count;
	}
		
	// Abstract
	protected string GetLayoutFile() {
		return string.Empty;
	}
	
	protected typename GetControllerType() {
		return Controller;
	}
	
	protected void Update();
	
	void Show()
	{
		if (m_LayoutRoot) {
			m_LayoutRoot.Show(true);
			if (m_UpdateQueue) {
				m_UpdateQueue.Insert(Update);
			}
		}
	}
	
	void Close()
	{
		if (m_LayoutRoot) {
			m_LayoutRoot.Show(false);
			m_LayoutRoot.Unlink();
			
			if (m_UpdateQueue) {
				m_UpdateQueue.Remove(Update);
			}
		}
	}
}