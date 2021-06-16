class CF_MultilineEditBoxWidget : CF_UIWidget
{
	private MultilineEditBoxWidget _MultilineEditBoxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineEditBoxWidget, w);
	}
};
