class CF_TextWidget : CF_UIWidget
{
	private TextWidget _TextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextWidget, w);
	}
};
