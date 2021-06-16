class CF_XComboBoxWidget : CF_UIWidget
{
	private XComboBoxWidget _XComboBoxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_XComboBoxWidget, w);
	}
};
