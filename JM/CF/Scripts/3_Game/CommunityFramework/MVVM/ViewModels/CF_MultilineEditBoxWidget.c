class CF_MultilineEditBoxWidget : CF_TextWidget
{
	reference string CarriageLine;
	reference string CarriagePosition;

	protected MultilineEditBoxWidget _MultilineEditBoxWidget;
	protected CF_TypeConverter _CarriageLine = CF_GetDefaultTC();
	protected CF_TypeConverter _CarriagePosition = CF_GetDefaultTC();

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

	override void OnView_Text(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());

		string value;
		_MultilineEditBoxWidget.GetText(value);
		_Text.SetString(value);
		_Text.ToVariable(m_Model, Text);
	}

	void OnView_CarriageLine(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_CarriageLine", "" + sender, args.ToStr());

		_CarriageLine.SetInt(_MultilineEditBoxWidget.GetCarriageLine());
		_CarriageLine.ToVariable(m_Model, CarriageLine);
	}

	void OnModel_CarriageLine(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_CarriageLine", "" + sender, args.ToStr());

		OnView_CarriageLine(m_Model, args);
	}

	void OnView_CarriagePosition(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_CarriagePosition", "" + sender, args.ToStr());

		_CarriagePosition.SetInt(_MultilineEditBoxWidget.GetCarriagePos());
		_CarriagePosition.ToVariable(m_Model, CarriagePosition);
	}

	void OnModel_CarriagePosition(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_CarriagePosition", "" + sender, args.ToStr());

		OnView_CarriagePosition(m_Model, args);
	}

	override bool OnChange(Class sender, CF_ChangeEventArgs args)
	{
		CF_Trace trace(this, "OnChange", args.ToStr());

		if (!args.Continue)
		{
		//	_MultilineEditBoxWidget.SetText(_Text);
		}

		//_MultilineEditBoxWidget.GetText(_Text);
		NotifyPropertyChanged(Text);

		return true;
	}
};