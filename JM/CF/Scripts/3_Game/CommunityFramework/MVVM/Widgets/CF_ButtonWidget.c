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
	protected CF_TypeConverter _State;
	protected CF_TypeConverter _Text;
	protected CF_TypeConverter _TextOffsetX;
	protected CF_TypeConverter _TextOffsetY;
	protected CF_TypeConverter _TextHorizontalAlignment;
	protected CF_TypeConverter _TextVerticalAlignment;
	protected CF_TypeConverter _TextProportion;

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

	void OnView_State(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_State", "" + model, evt.String());

		_State.SetBool(_ButtonWidget.GetState());
		_State.ToVariable(model, State);
	}

	void OnModel_State(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_State", "" + model, evt.String());
		
		_State.FromVariable(model, State);
		_ButtonWidget.SetState(_State.GetBool());
	}

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());
		
		_Text.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());
		
		_Text.FromVariable(model, Text);
		_ButtonWidget.SetText(_Text.GetString());
	}

	void OnView_TextOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOffsetX", "" + model, evt.String());
		
		_TextOffsetX.ToVariable(model, TextOffsetX);
	}

	void OnModel_TextOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOffsetX", "" + model, evt.String());
		
		_TextOffsetX.FromVariable(model, TextOffsetX);
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOffsetY", "" + model, evt.String());
		
		_TextOffsetX.ToVariable(model, TextOffsetX);
	}

	void OnModel_TextOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOffsetY", "" + model, evt.String());
		
		_TextOffsetY.FromVariable(model, TextOffsetY);
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextHorizontalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextHorizontalAlignment", "" + model, evt.String());
		
		_TextHorizontalAlignment.ToVariable(model, TextHorizontalAlignment);
	}

	void OnModel_TextHorizontalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextHorizontalAlignment", "" + model, evt.String());
		
		_TextHorizontalAlignment.FromVariable(model, TextHorizontalAlignment);
		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment.GetInt());
	}

	void OnView_TextVerticalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextVerticalAlignment", "" + model, evt.String());
		
		_TextVerticalAlignment.ToVariable(model, TextVerticalAlignment);
	}

	void OnModel_TextVerticalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextVerticalAlignment", "" + model, evt.String());
		
		_TextVerticalAlignment.FromVariable(model, TextVerticalAlignment);
		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment.GetInt());
	}

	void OnView_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextProportion", "" + model, evt.String());
		
		_TextProportion.SetInt(_ButtonWidget.GetTextProportion());
		_TextProportion.ToVariable(model, TextProportion);
	}

	void OnModel_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextProportion", "" + model, evt.String());
		
		_TextProportion.FromVariable(model, TextProportion);
		_ButtonWidget.SetTextProportion(_TextProportion.GetInt());
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (!evt.Continue)
		{
			_ButtonWidget.SetState(false);
		}

		NotifyPropertyChanged("State");

		return true;
	}
};
