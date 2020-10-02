static void LoadViewProperties(Class context, PropertyTypeHashMap property_map, Widget root_widget)
{
	foreach (string property_name, typename property_type: property_map) {
		
		if (property_type.IsInherited(Widget)) {
			Widget target = root_widget.FindAnyWidget(property_name);
			
			// fixes bug that breaks everything
			if (target && root_widget.GetName() != property_name) {
				EnScript.SetClassVar(context, property_name, 0, target);
			}
			
			// Allows you to define the layout root aswell within it
			if (!target && root_widget.GetName() == property_name) {
				EnScript.SetClassVar(context, property_name, 0, root_widget);
			}
		}
	}
}