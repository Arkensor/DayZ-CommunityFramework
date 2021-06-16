class CF_CheckBoxWidget : CF_UIWidget
{
	private CheckBoxWidget _CheckBoxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}
};
