class CF_RenderTargetWidget : CF_UIWidget
{
	protected RenderTargetWidget _RenderTargetWidget;

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RenderTargetWidget, w);
	}
};
