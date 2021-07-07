class CF_MultilineEditBoxWidget : CF_TextWidget
{
	reference string CarriageLine;
	reference string CarriagePosition;

	protected MultilineEditBoxWidget _MultilineEditBoxWidget;
	protected CF_TypeConverter _CarriageLine;
	protected CF_TypeConverter _CarriagePosition;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(CarriageLine, "CarriageLine");
		AddProperty(CarriagePosition, "CarriagePosition");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineEditBoxWidget, w);
	}

	override void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());

		string value;
		_MultilineEditBoxWidget.GetText(value);
		_Text.SetString(value);
		_Text.ToVariable(model, Text);
	}

	void OnView_CarriageLine(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_CarriageLine", "" + model, evt.String());

		_CarriageLine.SetInt(_MultilineEditBoxWidget.GetCarriageLine());
		_CarriageLine.ToVariable(model, CarriageLine);
	}

	void OnModel_CarriageLine(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_CarriageLine", "" + model, evt.String());

		OnView_CarriageLine(model, evt);
	}

	void OnView_CarriagePosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_CarriagePosition", "" + model, evt.String());

		_CarriagePosition.SetInt(_MultilineEditBoxWidget.GetCarriagePos());
		_CarriagePosition.ToVariable(model, CarriagePosition);
	}

	void OnModel_CarriagePosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_CarriagePosition", "" + model, evt.String());

		OnView_CarriagePosition(model, evt);
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (!evt.Continue)
		{
			_MultilineEditBoxWidget.SetText(_Text);
		}

		_MultilineEditBoxWidget.GetText(_Text);
		NotifyPropertyChanged("Text");

		return true;
	}
};
