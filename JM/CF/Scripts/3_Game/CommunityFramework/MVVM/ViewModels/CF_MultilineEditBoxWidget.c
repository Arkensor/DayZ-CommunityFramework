class CF_MultilineEditBoxWidget : CF_TextWidget
{
	reference string CarriageLine;
	reference string CarriagePosition;

	protected MultilineEditBoxWidget _MultilineEditBoxWidget;
	protected CF_MVVM_PropertyBase _CarriageLine = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _CarriagePosition = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(CarriageLine, "CarriageLine");
		AddProperty(CarriagePosition, "CarriagePosition");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineEditBoxWidget, w);
	}

	override void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		#endif

		string value;
		_MultilineEditBoxWidget.GetText(value);
		_Text.SetString(value);
	}

	void OnView_CarriageLine(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_CarriageLine", "" + sender, args.ToStr());
		#endif

		_CarriageLine.SetInt(_MultilineEditBoxWidget.GetCarriageLine());
	}

	void OnModel_CarriageLine(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_CarriageLine", "" + sender, args.ToStr());
		#endif

		OnView_CarriageLine(m_Model, args);
	}

	void OnView_CarriagePosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_CarriagePosition", "" + sender, args.ToStr());
		#endif

		_CarriagePosition.SetInt(_MultilineEditBoxWidget.GetCarriagePos());
	}

	void OnModel_CarriagePosition(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_CarriagePosition", "" + sender, args.ToStr());
		#endif

		OnView_CarriagePosition(m_Model, args);
	}

	override bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", args.ToStr());
		#endif

		if (!args.Continue)
		{
		//	_MultilineEditBoxWidget.SetText(_Text);
		}

		//_MultilineEditBoxWidget.GetText(_Text);
		NotifyPropertyChanged(Text, "Text");

		return true;
	}
};
