class CF_EditBoxWidget : CF_UIWidget
{
	private EditBoxWidget _EditBoxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_EditBoxWidget, w);
	}
};
