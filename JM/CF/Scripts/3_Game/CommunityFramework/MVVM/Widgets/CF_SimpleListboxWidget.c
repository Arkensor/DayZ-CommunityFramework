class CF_SimpleListboxWidget : CF_UIWidget
{
	private SimpleListboxWidget _SimpleListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SimpleListboxWidget, w);
	}
};
