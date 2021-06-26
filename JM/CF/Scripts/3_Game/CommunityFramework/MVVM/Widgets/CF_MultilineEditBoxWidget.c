class CF_MultilineEditBoxWidget : CF_TextWidget
{
	reference string CarriageLine;
	reference string CarriagePosition;

	protected MultilineEditBoxWidget _MultilineEditBoxWidget;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(CarriageLine, "CarriageLine");
		AddProperty(CarriagePosition, "CarriagePosition");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineEditBoxWidget, w);
	}

	override void OnView_Text(CF_ModelBase model, CF_Event evt)
	{
		_MultilineEditBoxWidget.GetText(_Text);
		EnScript.SetClassVar(model, Text, 0, _Text);
	}

	void OnView_CarriageLine(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, CarriageLine, 0, _MultilineEditBoxWidget.GetCarriageLine());
	}

	void OnModel_CarriageLine(CF_ModelBase model, CF_Event evt)
	{
		OnView_CarriageLine(model, evt);
	}

	void OnView_CarriagePosition(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, CarriagePosition, 0, _MultilineEditBoxWidget.GetCarriagePos());
	}

	void OnModel_CarriagePosition(CF_ModelBase model, CF_Event evt)
	{
		OnView_CarriagePosition(model, evt);
	}
};
