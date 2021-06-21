class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected string _Text;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_Model_Base model)
	{
		CF_MVVM_StringConverter.Set(model, Text, _Text);
	}

	void OnModel_Text(CF_Model_Base model)
	{
		CF_MVVM_StringConverter.Get(model, Text, _Text);
		_CheckBoxWidget.SetText(_Text);
	}

	void OnView_Checked(CF_Model_Base model)
	{
		bool _value = _CheckBoxWidget.IsChecked();
		EnScript.SetClassVar(model, Checked, 0, _value);
	}

	void OnModel_Checked(CF_Model_Base model)
	{
		bool _value;
		EnScript.GetClassVar(model, Checked, 0, _value);
		_CheckBoxWidget.SetChecked(_value);
	}
};
