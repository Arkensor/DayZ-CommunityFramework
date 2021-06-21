class CF_SimpleListboxWidget : CF_BaseListboxWidget
{
	protected SimpleListboxWidget _SimpleListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SimpleListboxWidget, w);
	}
};
