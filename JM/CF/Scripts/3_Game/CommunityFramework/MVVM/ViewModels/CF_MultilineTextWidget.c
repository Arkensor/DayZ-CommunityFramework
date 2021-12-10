class CF_MultilineTextWidget : CF_TextWidget
{
	protected MultilineTextWidget _MultilineTextWidget;

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineTextWidget, w);
	}
};
