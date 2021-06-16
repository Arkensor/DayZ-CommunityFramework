class CF_ButtonWidget : CF_UIWidget
{
	reference string State;
	reference string Text;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextHorizontalAlignment;
	reference string TextVerticalAlignment;
	reference string TextProportion;

	private ButtonWidget _ButtonWidget;
	private string _Text;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ButtonWidget, w);
	}
	
	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Text, "Text");
	}

	void OnView_Text(Class model)
	{
		EnScript.SetClassVar(model, Text, 0, _Text);
	}

	void OnModel_Text(Class model)
	{
		EnScript.GetClassVar(model, Text, 0, _Text);
		_ButtonWidget.SetText(_Text);
	}
};
