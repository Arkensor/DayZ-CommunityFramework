class CF_RenderTargetWidget : CF_UIWidget
{
	protected RenderTargetWidget _RenderTargetWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RenderTargetWidget, w);
	}
};
