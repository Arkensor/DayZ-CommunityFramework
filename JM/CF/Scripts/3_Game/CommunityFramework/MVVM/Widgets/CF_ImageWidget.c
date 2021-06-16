class CF_ImageWidget : CF_UIWidget
{
	private ImageWidget _ImageWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ImageWidget, w);
	}
};
