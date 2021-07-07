class CF_TextWidget : CF_Widget
{
	reference string Text;
	reference string TextSpacingHorizontal;
	reference string TextSpacingVertical;
	reference string TextExactSize;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextOutlineSize;
	reference string TextOutlineColor;
	reference string TextShadowSize;
	reference string TextShadowColor;
	reference string TextShadowOpacity;
	reference string TextShadowOffsetX;
	reference string TextShadowOffsetY;
	reference string TextItalic;
	reference string TextBold;
	reference string TextSizeX;
	reference string TextSizeY;
	reference string TextProportion;

	protected TextWidget _TextWidget;
	protected CF_TypeConverter _Text;
	protected CF_TypeConverter _TextSpacingHorizontal;
	protected CF_TypeConverter _TextSpacingVertical;
	protected CF_TypeConverter _TextExactSize;
	protected CF_TypeConverter _TextOffsetX;
	protected CF_TypeConverter _TextOffsetY;
	protected CF_TypeConverter _TextOutlineSize;
	protected CF_TypeConverter _TextOutlineColor;
	protected CF_TypeConverter _TextShadowSize;
	protected CF_TypeConverter _TextShadowColor;
	protected CF_TypeConverter _TextShadowOpacity;
	protected CF_TypeConverter _TextShadowOffsetX;
	protected CF_TypeConverter _TextShadowOffsetY;
	protected CF_TypeConverter _TextItalic;
	protected CF_TypeConverter _TextBold;
	protected CF_TypeConverter _TextSizeX;
	protected CF_TypeConverter _TextSizeY;
	protected CF_TypeConverter _TextProportion;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(TextSpacingHorizontal, "TextSpacingHorizontal");
		AddProperty(TextSpacingVertical, "TextSpacingVertical");
		AddProperty(TextExactSize, "TextExactSize");
		AddProperty(TextOffsetX, "TextOffsetX");
		AddProperty(TextOffsetY, "TextOffsetY");
		AddProperty(TextOutlineSize, "TextOutlineSize");
		AddProperty(TextOutlineColor, "TextOutlineColor");
		AddProperty(TextShadowSize, "TextShadowSize");
		AddProperty(TextShadowColor, "TextShadowColor");
		AddProperty(TextShadowOpacity, "TextShadowOpacity");
		AddProperty(TextShadowOffsetX, "TextShadowOffsetX");
		AddProperty(TextShadowOffsetY, "TextShadowOffsetY");
		AddProperty(TextItalic, "TextItalic");
		AddProperty(TextBold, "TextBold");
		AddProperty(TextSizeX, "TextSizeX");
		AddProperty(TextSizeY, "TextSizeY");
		AddProperty(TextProportion, "TextProportion");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextWidget, w);
	}

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());

		EnScript.SetClassVar(model, Text, 0, _Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());

		EnScript.GetClassVar(model, Text, 0, _Text);
		_TextWidget.SetText(_Text);
	}

	void OnView_TextSpacingHorizontal(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextSpacingHorizontal", "" + model, evt.String());

		EnScript.SetClassVar(model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
	}

	void OnModel_TextSpacingHorizontal(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextSpacingHorizontal", "" + model, evt.String());

		EnScript.GetClassVar(model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
		_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextSpacingVertical(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextSpacingVertical", "" + model, evt.String());

		EnScript.SetClassVar(model, TextSpacingVertical, 0, _TextSpacingVertical);
	}

	void OnModel_TextSpacingVertical(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextSpacingVertical", "" + model, evt.String());

		EnScript.GetClassVar(model, TextSpacingVertical, 0, TextSpacingVertical);
		_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextExactSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextExactSize", "" + model, evt.String());

		EnScript.SetClassVar(model, TextExactSize, 0, _TextExactSize);
	}

	void OnModel_TextExactSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextExactSize", "" + model, evt.String());

		EnScript.GetClassVar(model, TextExactSize, 0, _TextExactSize);
		_TextWidget.SetTextExactSize(_TextExactSize);
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
		_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
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
		_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOutlineSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOutlineSize", "" + model, evt.String());

		float _value = _TextWidget.GetOutlineSize();
		EnScript.SetClassVar(model, TextOutlineSize, 0, _value);
	}

	void OnModel_TextOutlineSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOutlineSize", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextOutlineSize, 0, _value);
		_TextWidget.SetOutline(_value, _TextWidget.GetOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextOutlineColor", "" + model, evt.String());

		float _value = _TextWidget.GetOutlineColor();
		EnScript.SetClassVar(model, TextOutlineColor, 0, _value);
	}

	void OnModel_TextOutlineColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextOutlineColor", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, TextOutlineColor, 0, _value);
		_TextWidget.SetOutline(_TextWidget.GetOutlineSize(), _value);
	}

	void OnView_TextShadowSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowSize", "" + model, evt.String());

		float _value = _TextWidget.GetShadowSize();
		EnScript.SetClassVar(model, TextShadowSize, 0, _value);
	}

	void OnModel_TextShadowSize(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowSize", "" + model, evt.String());

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(model, TextShadowSize, 0, _value);
		_TextWidget.SetShadow(_value, _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowColor", "" + model, evt.String());

		float _value = _TextWidget.GetShadowColor();
		EnScript.SetClassVar(model, TextShadowColor, 0, _value);
	}

	void OnModel_TextShadowColor(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowColor", "" + model, evt.String());

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(model, TextShadowColor, 0, _value);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _value, _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOpacity(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOpacity", "" + model, evt.String());

		float _value = _TextWidget.GetShadowOpacity();
		EnScript.SetClassVar(model, TextShadowOpacity, 0, _value);
	}

	void OnModel_TextShadowOpacity(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOpacity", "" + model, evt.String());

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		float _value;
		EnScript.GetClassVar(model, TextShadowOpacity, 0, _value);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _value, _sx, _sy);
	}

	void OnView_TextShadowOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetX", "" + model, evt.String());

		float _value, _other;
		_TextWidget.GetShadowOffset(_value, _other);
		EnScript.SetClassVar(model, TextShadowOffsetX, 0, _value);
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetX", "" + model, evt.String());

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(model, TextShadowOffsetX, 0, _sx);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetY", "" + model, evt.String());

		float _value, _other;
		_TextWidget.GetShadowOffset(_other, _value);
		EnScript.SetClassVar(model, TextShadowOffsetY, 0, _value);
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetY", "" + model, evt.String());

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(model, TextShadowOffsetY, 0, _sy);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextItalic(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextItalic", "" + model, evt.String());

		bool _value = _TextWidget.GetItalic();
		EnScript.SetClassVar(model, TextItalic, 0, _value);
	}

	void OnModel_TextItalic(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextItalic", "" + model, evt.String());

		bool _value;
		EnScript.GetClassVar(model, TextItalic, 0, _value);
		_TextWidget.SetItalic(_value);
	}

	void OnView_TextBold(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextBold", "" + model, evt.String());

		bool _value = _TextWidget.GetBold();
		EnScript.SetClassVar(model, TextBold, 0, _value);
	}

	void OnModel_TextBold(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextBold", "" + model, evt.String());

		bool _value;
		EnScript.GetClassVar(model, TextBold, 0, _value);
		_TextWidget.SetBold(_value);
	}

	void OnView_TextSizeX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextSizeX", "" + model, evt.String());

		int _value, _other;
		_TextWidget.GetTextSize(_value, _other);
		EnScript.SetClassVar(model, TextSizeX, 0, _value);
	}

	void OnModel_TextSizeX(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextSizeX", "" + model, evt.String());

		OnView_TextSizeX(model, evt);
	}

	void OnView_TextSizeY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextSizeY", "" + model, evt.String());

		int _value, _other;
		_TextWidget.GetTextSize(_other, _value);
		EnScript.SetClassVar(model, TextSizeY, 0, _value);
	}

	void OnModel_TextSizeY(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextSizeY", "" + model, evt.String());

		OnView_TextSizeY(model, evt);
	}

	void OnView_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_TextProportion", "" + model, evt.String());

		bool _value = _TextWidget.GetTextProportion();
		EnScript.SetClassVar(model, TextProportion, 0, _value);
	}

	void OnModel_TextProportion(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_TextProportion", "" + model, evt.String());

		bool _value;
		EnScript.GetClassVar(model, TextProportion, 0, _value);
		_TextWidget.SetTextProportion(_value);
	}
};
