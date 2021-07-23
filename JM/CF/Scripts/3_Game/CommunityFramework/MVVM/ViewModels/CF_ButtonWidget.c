class CF_ButtonWidget : CF_UIWidget
{
	reference string State;
	reference string Text;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextHorizontalAlignment;
	reference string TextVerticalAlignment;
	reference string TextProportion;

	protected ButtonWidget _ButtonWidget;
	protected CF_TypeConverter _State = CF_GetDefaultTC();
	protected CF_TypeConverter _Text = CF_GetDefaultTC();
	protected CF_TypeConverter _TextOffsetX = CF_GetDefaultTC();
	protected CF_TypeConverter _TextOffsetY = CF_GetDefaultTC();
	protected CF_TypeConverter _TextHorizontalAlignment = CF_GetDefaultTC();
	protected CF_TypeConverter _TextVerticalAlignment = CF_GetDefaultTC();
	protected CF_TypeConverter _TextProportion = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(State, "State");
		AddProperty(Text, "Text");
		AddProperty(TextOffsetX, "TextOffsetX");
		AddProperty(TextOffsetY, "TextOffsetY");
		AddProperty(TextHorizontalAlignment, "TextHorizontalAlignment");
		AddProperty(TextVerticalAlignment, "TextVerticalAlignment");
		AddProperty(TextProportion, "TextProportion");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ButtonWidget, w);
	}

	void OnView_State(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_State", "" + sender, args.ToStr());

		_State.SetBool(_ButtonWidget.GetState());
		_State.ToVariable(m_Model, State);
	}

	void OnModel_State(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_State", "" + sender, args.ToStr());
		
		_State.FromVariable(m_Model, State);
		_ButtonWidget.SetState(_State.GetBool());
	}

	void OnView_Text(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		
		_Text.ToVariable(m_Model, Text);
	}

	void OnModel_Text(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		
		_Text.FromVariable(m_Model, Text);
		_ButtonWidget.SetText(_Text.GetString());
	}

	void OnView_TextOffsetX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOffsetX", "" + sender, args.ToStr());
		
		_TextOffsetX.ToVariable(m_Model, TextOffsetX);
	}

	void OnModel_TextOffsetX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOffsetX", "" + sender, args.ToStr());
		
		_TextOffsetX.FromVariable(m_Model, TextOffsetX);
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextOffsetY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOffsetY", "" + sender, args.ToStr());
		
		_TextOffsetX.ToVariable(m_Model, TextOffsetX);
	}

	void OnModel_TextOffsetY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOffsetY", "" + sender, args.ToStr());
		
		_TextOffsetY.FromVariable(m_Model, TextOffsetY);
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextHorizontalAlignment(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextHorizontalAlignment", "" + sender, args.ToStr());
		
		_TextHorizontalAlignment.ToVariable(m_Model, TextHorizontalAlignment);
	}

	void OnModel_TextHorizontalAlignment(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextHorizontalAlignment", "" + sender, args.ToStr());
		
		_TextHorizontalAlignment.FromVariable(m_Model, TextHorizontalAlignment);
		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment.GetInt());
	}

	void OnView_TextVerticalAlignment(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextVerticalAlignment", "" + sender, args.ToStr());
		
		_TextVerticalAlignment.ToVariable(m_Model, TextVerticalAlignment);
	}

	void OnModel_TextVerticalAlignment(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextVerticalAlignment", "" + sender, args.ToStr());
		
		_TextVerticalAlignment.FromVariable(m_Model, TextVerticalAlignment);
		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment.GetInt());
	}

	void OnView_TextProportion(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextProportion", "" + sender, args.ToStr());
		
		_TextProportion.SetInt(_ButtonWidget.GetTextProportion());
		_TextProportion.ToVariable(m_Model, TextProportion);
	}

	void OnModel_TextProportion(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextProportion", "" + sender, args.ToStr());
		
		_TextProportion.FromVariable(m_Model, TextProportion);
		_ButtonWidget.SetTextProportion(_TextProportion.GetInt());
	}

	override bool OnChange(Class sender, CF_ChangeEventArgs args)
	{
		CF_Trace trace(this, "OnChange", args.ToStr());

		if (!args.Continue)
		{
			_ButtonWidget.SetState(false);
		}

		NotifyPropertyChanged(State);

		return true;
	}
};
