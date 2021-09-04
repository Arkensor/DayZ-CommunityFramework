class CF_RTTextureWidget : CF_UIWidget
{
	protected RTTextureWidget _RTTextureWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RTTextureWidget, w);
	}
};
