class CF_EditBoxWidget : CF_UIWidget
{
	reference string Text;

	protected EditBoxWidget _EditBoxWidget;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Text, "Text");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_EditBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase model, CF_Event evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.SetString(_EditBoxWidget.GetText());
		pType.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_Event evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.FromVariable(model, Text);
		_EditBoxWidget.SetText(pType.GetString());
	}
};
