
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
	

	
	// Generic Errors
	static void PropertyNotFoundError(string property_name)
	{
		PrintFormat("Property '%1' not found", property_name);
	}
	
	static void UnsupportedTypeError(typename type)
	{
		PrintFormat("Unsupported Type: %1", type.ToString());
	}
	
	static void UnsupportedConversionError(typename from_type, typename to_type)
	{
		PrintFormat("Unsupported conversion from %1 to %2!", from_type.ToString(), to_type.ToString());
	}
	
	static void TypeConversionError(typename property_type)
	{
		if (!property_type) {
			PrintFormat("Data Binding not found!");
		} else {
			PrintFormat("Could not find TypeConversion for Type %1\nUse MVC.RegisterConversionTemplates to register custom types", property_type.ToString());
		}
	}
	
	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		PrintFormat("MVCLog::Trace %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	static void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		PrintFormat(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
	}

	static void Error(string message)
	{
		//GetLogger().Error();
		Error2("MVC Error", message);
		
#ifdef COMPONENT_SYSTEM
		Workbench.Dialog("MVC Error", message);
#endif
	}	
}


// Abstract Class
class MVCWidgetHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
		
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
	}
}

// Abstract Class
class MVCLayout: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	
	protected PropertyHashMap m_PropertyHashMap = PropertyHashMap.FromType(Type());
	
	Widget GetLayoutRoot() {
		return m_LayoutRoot;
	}
	
	void MVCLayout()
	{
		string layout_file = GetLayoutFile();
		if (layout_file != string.Empty) {
			MVC.Trace("MVCLayout: %1", layout_file);
			m_LayoutRoot = GetGame().GetWorkspace().CreateWidgets(layout_file, null);
			if (m_LayoutRoot) {
				m_LayoutRoot.SetHandler(this);
				int property_count = LoadWidgets();
				MVC.Log("%1 properties found!", property_count.ToString());
			} else {
				MVC.Error("MVCLayout: Invalid layout file!");
			}
		} else {
			MVC.Error("MVCLayout: You must override GetLayoutFile with the .layout file path");
		}
	}
	
	int LoadWidgets()
	{
		int count;
		foreach (string property_name, typename property_type: m_PropertyHashMap) {
			Widget target = m_LayoutRoot.FindAnyWidget(property_name);
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
}

