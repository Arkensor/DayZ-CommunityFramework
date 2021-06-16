class CF_SimpleProgressBarWidget : CF_UIWidget
{
	private SimpleProgressBarWidget _SimpleProgressBarWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SimpleProgressBarWidget, w);
	}
};
