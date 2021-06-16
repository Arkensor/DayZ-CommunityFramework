class CF_RTTextureWidget : CF_UIWidget
{
	private RTTextureWidget _RTTextureWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RTTextureWidget, w);
	}
};
