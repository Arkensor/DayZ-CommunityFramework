static ref LayoutBindingManager g_LayoutBindingManager;

class LayoutBindingManager
{
	private static void CheckLayoutBindingManager()
	{
		if (!g_LayoutBindingManager)
		{ 
			g_LayoutBindingManager = new LayoutBindingManager();
		}
	}
	
	protected static ref TypenameHashMap m_WidgetControllerHashMap;
	static WidgetController GetWidgetController(Widget data) 
	{
		CheckLayoutBindingManager();
	
		WidgetController widgetController = WidgetController.Cast(m_WidgetControllerHashMap.Get(data.Type()).Spawn());
		g_Script.Call(widgetController, "SetWidget", data);
		return widgetController;
	}	
	
	protected static ref TypeConversionHashMap m_TypeConverterHashMap;
	static TypeConverter GetTypeConversion(typename type) 
	{
		CheckLayoutBindingManager();
				
		return TypeConverter.Cast(m_TypeConverterHashMap[type].Spawn()); 
	}
	
	void LayoutBindingManager()
	{
		Log("LayoutBindingManager");
		
		if (!m_TypeConverterHashMap)
		{
			m_TypeConverterHashMap = new TypeConversionHashMap();
			RegisterConversionTemplates(m_TypeConverterHashMap);
		}
		
		if (!m_WidgetControllerHashMap)
		{
			m_WidgetControllerHashMap = new TypenameHashMap();
			RegisterWidgetControllers(m_WidgetControllerHashMap);
		}
	}
	
	void ~LayoutBindingManager() 
	{ 
		Log("~LayoutBindingManager"); 
	}
	
	// Override THIS to add your own Custom Conversion Templates
	// this determines how data is represented in the UI itself
	// i.e. you can assign a TextWidget to float, due to the TypeConversion's GetString()
	void RegisterConversionTemplates(out TypeConversionHashMap conversions)
	{
		Log("LayoutBindingManager::RegisterConversionTemplates");
		conversions.Insert(bool, TypeConversionBool);
		conversions.Insert(int, TypeConversionInt);
		conversions.Insert(float, TypeConversionFloat);
		conversions.Insert(string, TypeConversionString);
		conversions.Insert(vector, TypeConversionVector);
		conversions.Insert(Widget, TypeConversionWidget);
		conversions.Insert(Object, TypeConversionObject);
		conversions.Insert(Observable, TypeConversionObservable);
		conversions.Insert(ScriptedViewBase, TypeConversionScriptView);
	}
	
	// Override THIS to add your own Widget Controllers 
	// this determins how the Widget controls the data sent to it
	// Great for prefabs
	void RegisterWidgetControllers(out TypenameHashMap controllers)
	{
		Log("LayoutBindingManager::RegisterWidgetControllers");
		
		controllers.Insert(Widget, WidgetBaseController);
		controllers.Insert(SpacerBaseWidget, SpacerBaseWidgetController);
		controllers.Insert(WrapSpacerWidget, SpacerBaseWidgetController);
		controllers.Insert(GridSpacerWidget, SpacerBaseWidgetController);
		controllers.Insert(ScrollWidget, SpacerBaseWidgetController);

		controllers.Insert(ButtonWidget, ButtonWidgetController);
		controllers.Insert(CheckBoxWidget, CheckBoxWidgetController);
		controllers.Insert(EditBoxWidget, EditBoxWidgetController);
		controllers.Insert(SliderWidget, SliderWidgetController);
		controllers.Insert(ProgressBarWidget, ProgressBarController);
		controllers.Insert(TextWidget, TextWidgetController);
		controllers.Insert(MultilineEditBoxWidget, MultilineEditBoxWidgetController);
		controllers.Insert(XComboBoxWidget, XComboBoxWidgetController);
		controllers.Insert(ImageWidget, ImageWidgetController);
		controllers.Insert(TextListboxWidget, TextListboxController);
		controllers.Insert(RichTextWidget, TextWidgetController);
		controllers.Insert(ItemPreviewWidget, ItemPreviewWidgetController);
	}	
	
	static void Trace(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (LBMLogLevel <= 0)
			PrintFormat("LayoutBindingManagerLog::Trace %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}
	
	static void Log(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		if (LBMLogLevel <= 1)
			PrintFormat("LayoutBindingManagerLog::Log %1", string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	}

	static void Error(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		string msg = string.Format(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		//PrintFormat("LayoutBindingManagerLog::Error %1", msg);
		Error2("LayoutBindingManager Error", msg);
		
#ifdef COMPONENT_SYSTEM
		Workbench.Dialog("LayoutBindingManager Error", msg);
#endif
	}
};

// Workbench safe variant of GetGame()
// https://feedback.bistudio.com/T153287
DayZGame GetWorkbenchGame() 
{
	// dont want to call this while actually in game
#ifdef COMPONENT_SYSTEM 
	if (!g_Game) {
		g_Game = new DayZGame();
	}
#endif
	
	return g_Game;
}