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

	void OnView_TextColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextColor", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, TextColor, 0, _TextColor);
	}

	void OnModel_TextColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextColor", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, TextColor, 0, _TextColor);
		//_UIWidget.SetTextColor(_TextColor);
	}

	void OnView_TextOutlineSize(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOutlineSize", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextOutlineSize();
		EnScript.SetClassVar(m_Model, TextOutlineSize, 0, _value);
	}

	void OnModel_TextOutlineSize(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOutlineSize", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextOutlineSize, 0, _value);
		_UIWidget.SetTextOutline(_value, _UIWidget.GetTextOutlineColor());
	}

	void OnView_TextOutlineColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOutlineColor", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextOutlineColor();
		EnScript.SetClassVar(m_Model, TextOutlineColor, 0, _value);
	}

	void OnModel_TextOutlineColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOutlineColor", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextOutlineColor, 0, _value);
		_UIWidget.SetTextOutline(_UIWidget.GetTextOutlineSize(), _value);
	}

	void OnView_TextShadowSize(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowSize", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextShadowSize();
		EnScript.SetClassVar(m_Model, TextShadowSize, 0, _value);
	}

	void OnModel_TextShadowSize(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowSize", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowSize, 0, _value);
		_UIWidget.SetTextShadow(_value, _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowColor", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextShadowColor();
		EnScript.SetClassVar(m_Model, TextShadowColor, 0, _value);
	}

	void OnModel_TextShadowColor(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowColor", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowColor, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _value, _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOpacity(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOpacity", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextShadowOpacity();
		EnScript.SetClassVar(m_Model, TextShadowOpacity, 0, _value);
	}

	void OnModel_TextShadowOpacity(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOpacity", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowOpacity, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _value, _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetX", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextShadowOffsetX();
		EnScript.SetClassVar(m_Model, TextShadowOffsetX, 0, _value);
	}

	void OnModel_TextShadowOffsetX(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetX", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowOffsetX, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _value, _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetY", "" + sender, args.ToStr());

		float _value = _UIWidget.GetTextShadowOffsetY();
		EnScript.SetClassVar(m_Model, TextShadowOffsetY, 0, _value);
	}

	void OnModel_TextShadowOffsetY(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetY", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowOffsetY, 0, _value);
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _value);
	}

	void OnView_TextItalic(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextItalic", "" + sender, args.ToStr());

		bool _value = _UIWidget.GetTextItalic();
		EnScript.SetClassVar(m_Model, TextItalic, 0, _value);
	}

	void OnModel_TextItalic(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextItalic", "" + sender, args.ToStr());

		bool _value;
		EnScript.GetClassVar(m_Model, TextItalic, 0, _value);
		_UIWidget.SetTextItalic(_value);
	}

	void OnView_TextBold(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextBold", "" + sender, args.ToStr());

		bool _value = _UIWidget.GetTextBold();
		EnScript.SetClassVar(m_Model, TextBold, 0, _value);
	}

	void OnModel_TextBold(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextBold", "" + sender, args.ToStr());

		bool _value;
		EnScript.GetClassVar(m_Model, TextBold, 0, _value);
		_UIWidget.SetTextBold(_value);
	}
};
