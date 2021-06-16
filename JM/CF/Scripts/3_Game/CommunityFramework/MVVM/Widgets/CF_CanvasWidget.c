class CF_CanvasWidget : CF_UIWidget
{
	private CanvasWidget _CanvasWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_CanvasWidget, w);
	}
};
