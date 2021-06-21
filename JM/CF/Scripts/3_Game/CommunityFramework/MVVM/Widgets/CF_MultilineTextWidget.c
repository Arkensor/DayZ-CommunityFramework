class CF_MultilineTextWidget : CF_TextWidget
{
	protected MultilineTextWidget _MultilineTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineTextWidget, w);
	}
};
