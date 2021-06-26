class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected string _Text;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(Checked, "Checked");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase model, CF_Event evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.SetString(_Text);
		pType.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_Event evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.FromVariable(model, Text);
		_CheckBoxWidget.SetText(pType.GetString());
	}

	void OnView_Checked(CF_ModelBase model, CF_Event evt)
	{
		bool _value = _CheckBoxWidget.IsChecked();
		EnScript.SetClassVar(model, Checked, 0, _value);
	}

	void OnModel_Checked(CF_ModelBase model, CF_Event evt)
	{
		bool _value;
		EnScript.GetClassVar(model, Checked, 0, _value);
		_CheckBoxWidget.SetChecked(_value);
	}
};
