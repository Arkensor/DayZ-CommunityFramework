class CF_WrapSpacerWidget : CF_SpacerWidget
{
	protected WrapSpacerWidget _WrapSpacerWidget;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_WrapSpacerWidget, w);
	}
};
