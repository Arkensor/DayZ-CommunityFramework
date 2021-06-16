class CF_TextListboxWidget : CF_UIWidget
{
	private TextListboxWidget _TextListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextListboxWidget, w);
	}
};
