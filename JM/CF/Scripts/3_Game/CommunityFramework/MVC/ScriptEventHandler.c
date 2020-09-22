

class ScriptedViewBase: ScriptedWidgetEventHandler
{
	ScriptedViewBase GetParent();
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (GetParent()) {
			return GetParent().OnClick(w, x, y, button);
		}
		
		return false;
	}
}