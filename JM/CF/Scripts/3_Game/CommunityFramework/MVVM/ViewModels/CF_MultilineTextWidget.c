class CF_MultilineTextWidget : CF_TextWidget
{
	protected MultilineTextWidget _MultilineTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineTextWidget, w);
	}
};
