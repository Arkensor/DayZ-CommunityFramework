class CF_WrapSpacerWidget : CF_SpacerWidget
{
	protected WrapSpacerWidget _WrapSpacerWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_WrapSpacerWidget, w);
	}
};
