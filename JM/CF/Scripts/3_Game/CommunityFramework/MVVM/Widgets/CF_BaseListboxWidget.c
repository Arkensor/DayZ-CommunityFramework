class CF_BaseListboxWidget : CF_UIWidget
{
	private BaseListboxWidget _BaseListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_BaseListboxWidget, w);
	}
};
