

// Loads .layout file Widgets into Properties of context (when they are the same name)
/*

Example:

.layout file:
MenuBarRoot		FrameWidget
	MenuBarFile   	ButtonWidget
		MenuBarFileLabel	TextWidget


.c file:
class TestClass
{
	ButtonWidget MenuBarFile; //<-- these properties will be assigned
	private TextWidget MenuBarFileLabel;
}

*/
static void LoadViewProperties(Class context, PropertyTypeHashMap property_map, Widget root_widget)
{
	foreach (string property_name, typename property_type: property_map) {
		
		if (!property_type.IsInherited(Widget)) continue;
		
		Widget target = root_widget.FindAnyWidget(property_name);
					
		// fixes bug that breaks everything
		if (target && root_widget.GetName() != property_name) {
			EnScript.SetClassVar(context, property_name, 0, target);
			continue;
		}
		
		// Allows you to define the layout root aswell within it
		if (!target && root_widget.GetName() == property_name) {
			EnScript.SetClassVar(context, property_name, 0, root_widget);
			continue;
		}
		
	}
}

// Gets typename from Templated type
// This is useful when getting this error...
// 'Can't get typename from forward declaration 'Class'. Use Type("name") instead....'
class TemplateType<Class T>
{
	T value;
	
	static typename GetType()
	{
		return (new TemplateType<T>()).Type().GetVariableType(0);
	}
}