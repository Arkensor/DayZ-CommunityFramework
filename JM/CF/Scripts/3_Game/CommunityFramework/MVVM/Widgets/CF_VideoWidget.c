class CF_VideoWidget : CF_UIWidget
{
	private VideoWidget _VideoWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_VideoWidget, w);
	}
};
