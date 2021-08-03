class CF_ProgressBarWidget : CF_SimpleProgressBarWidget
{
	protected ProgressBarWidget _ProgressBarWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ProgressBarWidget, w);
	}
};
