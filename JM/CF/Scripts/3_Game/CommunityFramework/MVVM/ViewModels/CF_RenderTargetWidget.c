class CF_RenderTargetWidget : CF_UIWidget
{
	protected RenderTargetWidget _RenderTargetWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RenderTargetWidget, w);
	}
};
