class CF_ProgressBarWidget : CF_SimpleProgressBarWidget
{
	protected ProgressBarWidget _ProgressBarWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ProgressBarWidget, w);
	}
};
