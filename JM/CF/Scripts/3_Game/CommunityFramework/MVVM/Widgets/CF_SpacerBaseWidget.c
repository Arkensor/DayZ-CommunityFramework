class CF_SpacerBaseWidget : CF_UIWidget
{
	protected SpacerBaseWidget _SpacerBaseWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerBaseWidget, w);
	}
};
