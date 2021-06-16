class CF_SliderWidget : CF_UIWidget
{
	private SliderWidget _SliderWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SliderWidget, w);
	}
};
