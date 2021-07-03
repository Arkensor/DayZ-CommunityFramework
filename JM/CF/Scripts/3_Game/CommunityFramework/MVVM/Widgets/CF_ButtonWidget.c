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
	protected string _Text;
	protected float _TextOffsetX;
	protected float _TextOffsetY;
	protected float _TextHorizontalAlignment;
	protected float _TextVerticalAlignment;

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
		
		bool _state = _ButtonWidget.GetState();
		EnScript.SetClassVar(model, State, 0, _state);
	}

	void OnModel_State(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_State", "" + model, evt.String());
		
		bool _state;
		EnScript.GetClassVar(model, State, 0, _state);
		_ButtonWidget.SetState(_state);
	}

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());
		
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.SetString(_Text);
		pType.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());
		
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.FromVariable(model, Text);
		_ButtonWidget.SetText(pType.GetString());
	}

	void OnView_TextOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOffsetX", "" + model, evt.String());
		
		EnScript.SetClassVar(model, TextOffsetX, 0, _TextOffsetX);
	}

	void OnModel_TextOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOffsetX", "" + model, evt.String());
		
		EnScript.GetClassVar(model, TextOffsetX, 0, _TextOffsetX);
		_ButtonWidget.SetTextOffset(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOffsetY", "" + model, evt.String());
		
		EnScript.SetClassVar(model, TextOffsetY, 0, _TextOffsetY);
	}

	void OnModel_TextOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOffsetY", "" + model, evt.String());
		
		EnScript.GetClassVar(model, TextOffsetY, 0, _TextOffsetY);
		_ButtonWidget.SetTextOffset(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextHorizontalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextHorizontalAlignment", "" + model, evt.String());
		
		EnScript.SetClassVar(model, TextHorizontalAlignment, 0, _TextHorizontalAlignment);
	}

	void OnModel_TextHorizontalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextHorizontalAlignment", "" + model, evt.String());
		
		EnScript.GetClassVar(model, TextHorizontalAlignment, 0, _TextHorizontalAlignment);
		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment);
	}

	void OnView_TextVerticalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextVerticalAlignment", "" + model, evt.String());
		
		EnScript.SetClassVar(model, TextVerticalAlignment, 0, _TextVerticalAlignment);
	}

	void OnModel_TextVerticalAlignment(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextVerticalAlignment", "" + model, evt.String());
		
		EnScript.GetClassVar(model, TextVerticalAlignment, 0, _TextVerticalAlignment);
		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment);
	}

	void OnView_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextProportion", "" + model, evt.String());
		
		float _TextProportion = _ButtonWidget.GetTextProportion();
		EnScript.SetClassVar(model, TextProportion, 0, _TextProportion);
	}

	void OnModel_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextProportion", "" + model, evt.String());
		
		float _TextProportion;
		EnScript.GetClassVar(model, TextProportion, 0, _TextProportion);
		_ButtonWidget.SetTextProportion(_TextProportion);
	}
};
