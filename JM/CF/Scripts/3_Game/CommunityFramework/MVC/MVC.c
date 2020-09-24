

// Helps workbench not crash, as a result of GetGame()
DayZGame GetWorkbenchGame(bool force = false) 
{
	if (!g_Game || force) {
		g_Game = new DayZGame();
	}
	
	return g_Game;
}


static ref MVC _MVC;

class MVC
{
	
	protected static ref TypenameHashMap m_WidgetControllerHashMap;
	static WidgetController GetWidgetController(Class data) 
	{
		if (!_MVC) _MVC = new MVC();
	
		WidgetController widget_controller = m_WidgetControllerHashMap.Get(data.Type()).Spawn();
		g_Script.Call(widget_controller, "SetWidget", data);
		return widget_controller;
	}
	
	
	protected static ref TypeConversionHashMap m_TypeConverterHashMap;
	static TypeConverter GetTypeConversion(typename type) 
	{
		if (!_MVC) _MVC = new MVC();
		
		if (type.IsInherited(Observable)) {
			type = Observable.Cast(type.Spawn()).GetType();
		}
		
		return m_TypeConverterHashMap.Get(type).Spawn(); 
	}
	
	void MVC()
	{
		Trace("MVC");
		
		if (!g_Game) {
			g_Game = new DayZGame();
		}
		
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
		Trace("~MVC"); 
	}
	
	// Override THIS to add your own Custom Conversion Templates
	// this determines how data is represented in the UI itself
	// i.e. you can assign a TextWidget to float, due to the TypeConversion's GetString()
	void RegisterConversionTemplates(out TypeConversionHashMap type_conversions)
	{
		Trace("MVC::RegisterConversionTemplates");
		type_conversions.Insert(bool, TypeConversionBool);
		type_conversions.Insert(int, TypeConversionInt);
		type_conversions.Insert(float, TypeConversionFloat);
		type_conversions.Insert(string, TypeConversionString);
		type_conversions.Insert(vector, TypeConversionVector);
		type_conversions.Insert(Widget, TypeConversionWidget);
		type_conversions.Insert(Object, TypeConversionObject);
		type_conversions.Insert(ObservableSet, TypeConversionObservable);
		type_conversions.Insert(ObservableCollection, TypeConversionObservable);
		type_conversions.Insert(ObservableDictionary, TypeConversionObservable);
		type_conversions.Insert(ScriptedViewBase, TypeConversionScriptView);
	}
	
	// Override THIS to add your own Widget Controllers 
	// this determins how the Widget controls the data sent to it
	// Great for prefabs
	void RegisterWidgetControllers(out TypenameHashMap widget_controllers)
	{
		Trace("MVC::RegisterWidgetControllers");
		widget_controllers.Insert(Widget, SpacerWidgetController);
		widget_controllers.Insert(SpacerWidget, SpacerWidgetController);
		widget_controllers.Insert(GridSpacerWidget, SpacerWidgetController);
		widget_controllers.Insert(WrapSpacerWidget, SpacerWidgetController);
		
		widget_controllers.Insert(ButtonWidget, ButtonWidgetController);
		widget_controllers.Insert(CheckBoxWidget, CheckBoxWidgetController);
		widget_controllers.Insert(EditBoxWidget, EditBoxWidgetController);
		widget_controllers.Insert(SliderWidget, SliderWidgetController);
		widget_controllers.Insert(ProgressBarWidget, ProgressBarController);
		widget_controllers.Insert(TextWidget, TextWidgetController);
		widget_controllers.Insert(MultilineEditBoxWidget, MultilineEditBoxWidgetController);
		widget_controllers.Insert(XComboBoxWidget, XComboBoxWidgetController);
		widget_controllers.Insert(ImageWidget, ImageWidgetController);
		widget_controllers.Insert(TextListboxWidget, TextListboxController);
		widget_controllers.Insert(RichTextWidget, TextWidgetController);
		widget_controllers.Insert(ItemPreviewWidget, ItemPreviewWidgetController);
	}
		
	static int LogLevel = 0;
	
	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (LogLevel <= 0)
			PrintFormat("MVCLog::Trace %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	static void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (LogLevel <= 1)
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




