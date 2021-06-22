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
	protected string _Text;
	protected float _TextSpacingHorizontal;
	protected float _TextSpacingVertical;
	protected float _TextExactSize;
	protected float _TextOffsetX;
	protected float _TextOffsetY;

	override void GetProperties()
	{
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
		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextWidget, w);
	}

	void OnView_Text(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, Text, 0, _Text);
	}

	void OnModel_Text(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, Text, 0, _Text);
		_TextWidget.SetText(_Text);
	}

	void OnView_TextSpacingHorizontal(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
	}

	void OnModel_TextSpacingHorizontal(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
		_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextSpacingVertical(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextSpacingVertical, 0, _TextSpacingVertical);
	}

	void OnModel_TextSpacingVertical(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextSpacingVertical, 0, TextSpacingVertical);
		_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextExactSize(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextExactSize, 0, _TextExactSize);
	}

	void OnModel_TextExactSize(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextExactSize, 0, _TextExactSize);
		_TextWidget.SetTextExactSize(_TextExactSize);
	}

	void OnView_TextOffsetX(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextOffsetX, 0, _TextOffsetX);
	}

	void OnModel_TextOffsetX(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextOffsetX, 0, _TextOffsetX);
		_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOffsetY(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextOffsetY, 0, _TextOffsetY);
	}

	void OnModel_TextOffsetY(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextOffsetY, 0, _TextOffsetY);
		_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOutlineSize(CF_Model_Base model)
	{
		float _value = _TextWidget.GetOutlineSize();
		EnScript.SetClassVar(model, TextOutlineSize, 0, _value);
	}

	void OnModel_TextOutlineSize(CF_Model_Base model)
	{
		float _value;
		EnScript.GetClassVar(model, TextOutlineSize, 0, _value);
		_TextWidget.SetOutline(_value, _TextWidget.GetOutlineColor());
	}

	void OnView_TextOutlineColor(CF_Model_Base model)
	{
		float _value = _TextWidget.GetOutlineColor();
		EnScript.SetClassVar(model, TextOutlineColor, 0, _value);
	}

	void OnModel_TextOutlineColor(CF_Model_Base model)
	{
		float _value;
		EnScript.GetClassVar(model, TextOutlineColor, 0, _value);
		_TextWidget.SetOutline(_TextWidget.GetOutlineSize(), _value);
	}

	void OnView_TextShadowSize(CF_Model_Base model)
	{
		float _value = _TextWidget.GetShadowSize();
		EnScript.SetClassVar(model, TextShadowSize, 0, _value);
	}

	void OnModel_TextShadowSize(CF_Model_Base model)
	{
		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(model, TextShadowSize, 0, _value);
		_TextWidget.SetShadow(_value, _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowColor(CF_Model_Base model)
	{
		float _value = _TextWidget.GetShadowColor();
		EnScript.SetClassVar(model, TextShadowColor, 0, _value);
	}

	void OnModel_TextShadowColor(CF_Model_Base model)
	{
		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(model, TextShadowColor, 0, _value);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _value, _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOpacity(CF_Model_Base model)
	{
		float _value = _TextWidget.GetShadowOpacity();
		EnScript.SetClassVar(model, TextShadowOpacity, 0, _value);
	}

	void OnModel_TextShadowOpacity(CF_Model_Base model)
	{
		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		float _value;
		EnScript.GetClassVar(model, TextShadowOpacity, 0, _value);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _value, _sx, _sy);
	}

	void OnView_TextShadowOffsetX(CF_Model_Base model)
	{
		float _value, _other;
		_TextWidget.GetShadowOffset(_value, _other);
		EnScript.SetClassVar(model, TextShadowOffsetX, 0, _value);
	}

	void OnModel_TextShadowOffsetX(CF_Model_Base model)
	{
		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(model, TextShadowOffsetX, 0, _sx);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOffsetY(CF_Model_Base model)
	{
		float _value, _other;
		_TextWidget.GetShadowOffset(_other, _value);
		EnScript.SetClassVar(model, TextShadowOffsetY, 0, _value);
	}

	void OnModel_TextShadowOffsetY(CF_Model_Base model)
	{
		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(model, TextShadowOffsetY, 0, _sy);
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextItalic(CF_Model_Base model)
	{
		bool _value = _TextWidget.GetItalic();
		EnScript.SetClassVar(model, TextItalic, 0, _value);
	}

	void OnModel_TextItalic(CF_Model_Base model)
	{
		bool _value;
		EnScript.GetClassVar(model, TextItalic, 0, _value);
		_TextWidget.SetItalic(_value);
	}

	void OnView_TextBold(CF_Model_Base model)
	{
		bool _value = _TextWidget.GetBold();
		EnScript.SetClassVar(model, TextBold, 0, _value);
	}

	void OnModel_TextBold(CF_Model_Base model)
	{
		bool _value;
		EnScript.GetClassVar(model, TextBold, 0, _value);
		_TextWidget.SetBold(_value);
	}

	void OnView_TextSizeX(CF_Model_Base model)
	{
		int _value, _other;
		_TextWidget.GetTextSize(_value, _other);
		EnScript.SetClassVar(model, TextSizeX, 0, _value);
	}

	void OnModel_TextSizeX(CF_Model_Base model)
	{
		OnView_TextSizeX(model);
	}

	void OnView_TextSizeY(CF_Model_Base model)
	{
		int _value, _other;
		_TextWidget.GetTextSize(_other, _value);
		EnScript.SetClassVar(model, TextSizeY, 0, _value);
	}

	void OnModel_TextSizeY(CF_Model_Base model)
	{
		OnView_TextSizeY(model);
	}

	void OnView_TextProportion(CF_Model_Base model)
	{
		bool _value = _TextWidget.GetTextProportion();
		EnScript.SetClassVar(model, TextProportion, 0, _value);
	}

	void OnModel_TextProportion(CF_Model_Base model)
	{
		bool _value;
		EnScript.GetClassVar(model, TextProportion, 0, _value);
		_TextWidget.SetTextProportion(_value);
	}
};
