
static ref MVC _MVC;

class MVC
{
	
	protected static ref TypenameHashMap m_WidgetControllerHashMap;
	static WidgetController GetWidgetController(Class data)
	{
		if (!_MVC) {
			_MVC = new MVC();
		}
	
		WidgetController widget_controller = m_WidgetControllerHashMap.Get(data.Type()).Spawn();
		g_Script.Call(widget_controller, "SetWidget", data);
		return widget_controller;
	}
	
	
	protected static ref TypeConversionHashMap m_TypeConverterHashMap;
	static TypeConverter GetTypeConversion(typename type) 
	{
		if (!_MVC) {
			_MVC = new MVC();
		}
		// todo remove
		//_MVC = new MVC();
		
		return m_TypeConverterHashMap.Get(type).Spawn(); 
	}
	
	void MVC()
	{
		GetLogger().Log("MVC", "JM_CF_MVC");
		if (!m_TypeConverterHashMap) {
			m_TypeConverterHashMap = new TypeConversionHashMap();
			RegisterConversionTemplates(m_TypeConverterHashMap);
		}
		
		if (!m_WidgetControllerHashMap) {
			m_WidgetControllerHashMap = new TypenameHashMap();
			RegisterWidgetControllers(m_WidgetControllerHashMap);
		}
	}
	
	void ~MVC() { 
		GetLogger().Log("~MVC", "JM_CF_MVC"); 
	}
	
	// Override THIS to add your own Custom Conversion Templates
	void RegisterConversionTemplates(out TypeConversionHashMap type_conversions)
	{
		GetLogger().Log("MVC::RegisterConversionTemplates", "JM_CF_MVC");
		type_conversions.Insert(bool, TypeConversionBool);
		type_conversions.Insert(int, TypeConversionInt);
		type_conversions.Insert(float, TypeConversionFloat);
		type_conversions.Insert(string, TypeConversionString);
		type_conversions.Insert(vector, TypeConversionVector);
		type_conversions.Insert(Widget, TypeConversionWidget);
	}
	
	void RegisterWidgetControllers(out TypenameHashMap widget_controllers)
	{
		GetLogger().Log("MVC::RegisterWidgetControllers", "JM_CF_MVC");
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
	

	
	
	static void PropertyNotFoundError(string property_name)
	{
		GetLogger().Log(string.Format("Property '%1' not found", property_name), "JM_CF_MVC");
	}
	
	static void UnsupportedTypeError(typename type)
	{
		GetLogger().Log(string.Format("Unsupported Type: %1", type.ToString()), "JM_CF_MVC");
	}
	
	static void UnsupportedConversionError(typename from_type, typename to_type)
	{
		GetLogger().Log(string.Format("Unsupported conversion from %1 to %2!", from_type.ToString(), to_type.ToString()), "JM_CF_MVC");
	}
	
	static void TypeConversionError(typename property_type)
	{
		if (!property_type) {
			GetLogger().Log("Data Binding not found!", "JM_CF_MVC");
		} else {
			GetLogger().Log(string.Format("Could not find TypeConversion for Type %1\nUse MVC.RegisterConversionTemplates to register custom types", property_type.ToString()), "JM_CF_MVC");
		}
	}
	

	
}

