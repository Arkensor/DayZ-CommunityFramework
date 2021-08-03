class CF_RTTextureWidget : CF_UIWidget
{
	protected RTTextureWidget _RTTextureWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RTTextureWidget, w);
	}
};
