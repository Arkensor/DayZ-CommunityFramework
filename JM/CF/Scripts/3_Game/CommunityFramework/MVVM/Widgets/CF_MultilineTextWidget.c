class CF_MultilineTextWidget : CF_TextWidget
{
	protected MultilineTextWidget _MultilineTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineTextWidget, w);
	}
};
