class CF_ScrollWidget : CF_UIWidget
{
	private ScrollWidget _ScrollWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ScrollWidget, w);
	}
};
