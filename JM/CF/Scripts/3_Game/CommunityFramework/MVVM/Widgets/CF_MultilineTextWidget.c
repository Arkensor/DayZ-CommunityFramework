class CF_MultilineTextWidget : CF_UIWidget
{
	private MultilineTextWidget _MultilineTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineTextWidget, w);
	}
};
