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

	void OnView_Text(CF_Model_Base model, CF_Event evt)
	{
		string _text = _EditBoxWidget.GetText();
		CF_MVVM_StringConverter.Set(model, Text, _text);
	}

	void OnModel_Text(CF_Model_Base model, CF_Event evt)
	{
		string _text;
		CF_MVVM_StringConverter.Get(model, Text, _text);
		_EditBoxWidget.SetText(_text);
	}
};
