class CF_UIWidget : CF_Widget
{
	reference string TextColor;
	reference string TextOutlineSize;
	reference string TextOutlineColor;
	reference string TextShadowSize;
	reference string TextShadowColor;
	reference string TextShadowOpacity;
	reference string TextShadowOffsetX;
	reference string TextShadowOffsetY;
	reference string TextItalic;
	reference string TextBold;
	
	protected UIWidget _UIWidget;
	protected CF_TypeConverter _TextColor;
	protected CF_TypeConverter _TextOutlineSize;
	protected CF_TypeConverter _TextOutlineColor;
	protected CF_TypeConverter _TextShadowSize;
	protected CF_TypeConverter _TextShadowColor;
	protected CF_TypeConverter _TextShadowOpacity;
	protected CF_TypeConverter _TextShadowOffsetX;
	protected CF_TypeConverter _TextShadowOffsetY;
	protected CF_TypeConverter _TextItalic;
	protected CF_TypeConverter _TextBold;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(TextColor, "TextColor");
		AddProperty(TextOutlineSize, "TextOutlineSize");
		AddProperty(TextOutlineColor, "TextOutlineColor");
		AddProperty(TextShadowSize, "TextShadowSize");
		AddProperty(TextShadowColor, "TextShadowColor");
		AddProperty(TextShadowOpacity, "TextShadowOpacity");
		AddProperty(TextShadowOffsetX, "TextShadowOffsetX");
		AddProperty(TextShadowOffsetY, "TextShadowOffsetY");
		AddProperty(TextItalic, "TextItalic");
		AddProperty(TextBold, "TextBold");
	}
	
	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_UIWidget, w);
	}

	void OnView_TextColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextColor", "" + model, evt.String());

		EnScript.SetClassVar(model, TextColor, 0, _TextColor);
	}

	void OnModel_TextColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextColor", "" + model, evt.String());

		EnScript.GetClassVar(model, TextColor, 0, _TextColor);
		_UIWidget.SetTextColor(_TextColor);
	}

	void OnView_TextOutlineSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOutlineSize", "" + model, evt.String());

		float _value = _UIWidget.GetTextOutlineSize();
		EnScript.SetClassVar(model, TextOutlineSize, 0, _value);
	}

	void OnModel_TextOutlineSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOutlineSize", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextOutlineSize, 0, _value);
		_UIWidget.SetTextOutline(_value, _UIWidget.GetTextOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOutlineColor", "" + model, evt.String());

		float _value = _UIWidget.GetTextOutlineColor();
		EnScript.SetClassVar(model, TextOutlineColor, 0, _value);
	}

	void OnModel_TextOutlineColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOutlineColor", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextOutlineColor, 0, _value);
		_UIWidget.SetTextOutline(_UIWidget.GetTextOutlineSize(), _value);
	}

	void OnView_TextShadowSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowSize", "" + model, evt.String());

		float _value = _UIWidget.GetTextShadowSize();
		EnScript.SetClassVar(model, TextShadowSize, 0, _value);
	}

	void OnModel_TextShadowSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowSize", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextShadowSize, 0, _value);
		_UIWidget.SetTextShadow(_value, _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowColor", "" + model, evt.String());

		float _value = _UIWidget.GetTextShadowColor();
		EnScript.SetClassVar(model, TextShadowColor, 0, _value);
	}

	void OnModel_TextShadowColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowColor", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextShadowColor, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _value, _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOpacity(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOpacity", "" + model, evt.String());

		float _value = _UIWidget.GetTextShadowOpacity();
		EnScript.SetClassVar(model, TextShadowOpacity, 0, _value);
	}

	void OnModel_TextShadowOpacity(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOpacity", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextShadowOpacity, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _value, _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetX", "" + model, evt.String());

		float _value = _UIWidget.GetTextShadowOffsetX();
		EnScript.SetClassVar(model, TextShadowOffsetX, 0, _value);
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetX", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextShadowOffsetX, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _value, _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetY", "" + model, evt.String());

		float _value = _UIWidget.GetTextShadowOffsetY();
		EnScript.SetClassVar(model, TextShadowOffsetY, 0, _value);
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetY", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextShadowOffsetY, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _value);
	}

	void OnView_TextItalic(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextItalic", "" + model, evt.String());

		bool _value = _UIWidget.GetTextItalic();
		EnScript.SetClassVar(model, TextItalic, 0, _value);
	}

	void OnModel_TextItalic(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextItalic", "" + model, evt.String());

		bool _value;
		EnScript.GetClassVar(model, TextItalic, 0, _value);
		_UIWidget.SetTextItalic(_value);
	}

	void OnView_TextBold(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextBold", "" + model, evt.String());

		bool _value = _UIWidget.GetTextBold();
		EnScript.SetClassVar(model, TextBold, 0, _value);
	}

	void OnModel_TextBold(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextBold", "" + model, evt.String());

		bool _value;
		EnScript.GetClassVar(model, TextBold, 0, _value);
		_UIWidget.SetTextBold(_value);
	}
};
