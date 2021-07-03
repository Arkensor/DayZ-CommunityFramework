class CF_RTTextureWidget : CF_UIWidget
{
	protected RTTextureWidget _RTTextureWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RTTextureWidget, w);
	}
};
