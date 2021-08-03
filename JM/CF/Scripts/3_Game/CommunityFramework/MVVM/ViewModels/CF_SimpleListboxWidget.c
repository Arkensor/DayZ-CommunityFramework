class CF_SimpleListboxWidget : CF_BaseListboxWidget
{
	protected SimpleListboxWidget _SimpleListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SimpleListboxWidget, w);
	}
};
