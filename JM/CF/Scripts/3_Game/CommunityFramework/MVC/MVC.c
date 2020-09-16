
static ref MVC _MVC;

class MVC
{
	protected static ref TypenameHashMap m_WidgetControllerHashMap;
	static WidgetController GetWidgetController(Class data) {
		if (!_MVC)
			_MVC = new MVC();
	
		WidgetController widget_controller = m_WidgetControllerHashMap.Get(data.Type()).Spawn();
		g_Script.Call(widget_controller, "SetWidget", data);
		return widget_controller;
	}
	
	
	protected static ref TypeConversionHashMap m_TypeConverterHashMap;
	static TypeConverter GetTypeConversion(typename type) {
		if (!_MVC)
			_MVC = new MVC();
		
		return m_TypeConverterHashMap.Get(type).Spawn(); 
	}
	
	void MVC()
	{
		//GetLogger().Log("MVC", "JM_CF_MVC");
		if (!m_TypeConverterHashMap) {
			m_TypeConverterHashMap = new TypeConversionHashMap();
			RegisterConversionTemplates(m_TypeConverterHashMap);
		}
		
		if (!m_WidgetControllerHashMap) {
			m_WidgetControllerHashMap = new TypenameHashMap();
			RegisterWidgetControllers(m_WidgetControllerHashMap);
		}
	}
	
	void ~MVC() 
	{ 
		//GetLogger().Log("~MVC", "JM_CF_MVC"); 
	}
	
	// Override THIS to add your own Custom Conversion Templates
	// this determines how data is represented in the UI itself
	// i.e. you can assign a TextWidget to float, due to the TypeConversion's GetString()
	void RegisterConversionTemplates(out TypeConversionHashMap type_conversions)
	{
		//GetLogger().Log("MVC::RegisterConversionTemplates", "JM_CF_MVC");
		type_conversions.Insert(bool, TypeConversionBool);
		type_conversions.Insert(int, TypeConversionInt);
		type_conversions.Insert(float, TypeConversionFloat);
		type_conversions.Insert(string, TypeConversionString);
		type_conversions.Insert(vector, TypeConversionVector);
		type_conversions.Insert(Widget, TypeConversionWidget);
	}
	
	// Override THIS to add your own Widget Controllers 
	// this determins how the Widget controls the data sent to it
	// Great for prefabs
	void RegisterWidgetControllers(out TypenameHashMap widget_controllers)
	{
		//GetLogger().Log("MVC::RegisterWidgetControllers", "JM_CF_MVC");
		widget_controllers.Insert(Widget, SpacerWidgetController);
		widget_controllers.Insert(SpacerWidget, SpacerWidgetController);
		widget_controllers.Insert(GridSpacerWidget, SpacerWidgetController);
		widget_controllers.Insert(WrapSpacerWidget, SpacerWidgetController);
		
		widget_controllers.Insert(ButtonWidget, ButtonWidgetController);
		widget_controllers.Insert(CheckBoxWidget, CheckBoxWidgetController);
		widget_controllers.Insert(EditBoxWidget, EditBoxWidgetController);
		widget_controllers.Insert(SliderWidget, SliderWidgetController);
		widget_controllers.Insert(TextWidget, TextWidgetController);
		widget_controllers.Insert(MultilineEditBoxWidget, MultilineEditBoxWidgetController);
		widget_controllers.Insert(XComboBoxWidget, XComboBoxWidgetController);
		widget_controllers.Insert(ImageWidget, ImageWidgetController);
		widget_controllers.Insert(TextListboxWidget, TextListboxController);		
	}
	

	
	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		PrintFormat("MVCLog::Trace %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	static void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		PrintFormat("MVCLog::Log %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		//PrintFormat("MVCLog::Error %1", msg);
		Error2("MVC Error", msg);
		
#ifdef COMPONENT_SYSTEM
		Workbench.Dialog("MVC Error", msg);
#endif
	}	
}

// Abstract Class
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
			MVC.Log("MVCLayout: Workspace was null, try reloading Workbench");
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

