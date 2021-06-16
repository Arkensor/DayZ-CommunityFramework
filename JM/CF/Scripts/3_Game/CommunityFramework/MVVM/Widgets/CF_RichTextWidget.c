class CF_RichTextWidget : CF_UIWidget
{
	private RichTextWidget _RichTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RichTextWidget, w);
	}
};
