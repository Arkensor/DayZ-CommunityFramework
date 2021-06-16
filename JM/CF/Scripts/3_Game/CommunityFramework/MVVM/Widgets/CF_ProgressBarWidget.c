class CF_ProgressBarWidget : CF_UIWidget
{
	private ProgressBarWidget _ProgressBarWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ProgressBarWidget, w);
	}
};
