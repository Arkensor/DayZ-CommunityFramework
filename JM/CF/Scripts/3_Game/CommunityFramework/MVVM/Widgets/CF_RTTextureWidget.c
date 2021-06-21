class CF_RTTextureWidget : CF_UIWidget
{
	protected RTTextureWidget _RTTextureWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RTTextureWidget, w);
	}
};
