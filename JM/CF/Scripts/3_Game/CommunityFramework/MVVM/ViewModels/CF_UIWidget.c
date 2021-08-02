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
	protected CF_TypeConverter _TextColor = CF_GetDefaultTC();
	protected CF_TypeConverter _TextOutlineSize = CF_GetDefaultTC();
	protected CF_TypeConverter _TextOutlineColor = CF_GetDefaultTC();
	protected CF_TypeConverter _TextShadowSize = CF_GetDefaultTC();
	protected CF_TypeConverter _TextShadowColor = CF_GetDefaultTC();
	protected CF_TypeConverter _TextShadowOpacity = CF_GetDefaultTC();
	protected CF_TypeConverter _TextShadowOffsetX = CF_GetDefaultTC();
	protected CF_TypeConverter _TextShadowOffsetY = CF_GetDefaultTC();
	protected CF_TypeConverter _TextItalic = CF_GetDefaultTC();
	protected CF_TypeConverter _TextBold = CF_GetDefaultTC();

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

	void OnView_TextColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextColor", "" + sender, args.ToStr());

		OnModel_TextColor(sender, args);
	}

	void OnModel_TextColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextColor", "" + sender, args.ToStr());

		_TextColor.FromVariable(m_Model, TextColor);
		_UIWidget.SetTextColor(_TextColor.GetInt());
	}

	void OnView_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOutlineSize", "" + sender, args.ToStr());

		_TextOutlineSize.SetFloat(_UIWidget.GetTextOutlineSize());
		_TextOutlineSize.ToVariable(m_Model, TextOutlineSize);
	}

	void OnModel_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOutlineSize", "" + sender, args.ToStr());

		_TextOutlineSize.FromVariable(m_Model, TextOutlineSize);
		_UIWidget.SetTextOutline(_TextOutlineSize.GetFloat(), _UIWidget.GetTextOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextOutlineColor", "" + sender, args.ToStr());

		_TextOutlineColor.SetFloat(_UIWidget.GetTextOutlineColor());
		_TextOutlineColor.ToVariable(m_Model, TextOutlineColor);
	}

	void OnModel_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextOutlineColor", "" + sender, args.ToStr());

		_TextOutlineColor.FromVariable(m_Model, TextOutlineColor);
		_UIWidget.SetTextOutline(_UIWidget.GetTextOutlineSize(), _TextOutlineColor.GetFloat());
	}

	void OnView_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowSize", "" + sender, args.ToStr());

		_TextShadowSize.SetFloat(_UIWidget.GetTextShadowSize());
		_TextShadowSize.ToVariable(m_Model, TextShadowSize);
	}

	void OnModel_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowSize", "" + sender, args.ToStr());
		
		_TextShadowSize.FromVariable(m_Model, TextShadowSize);
		_UIWidget.SetTextShadow(_TextShadowSize.GetFloat(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowColor", "" + sender, args.ToStr());

		_TextShadowColor.SetFloat(_UIWidget.GetTextShadowColor());
		_TextShadowColor.ToVariable(m_Model, TextShadowColor);
	}

	void OnModel_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowColor", "" + sender, args.ToStr());

		_TextShadowColor.FromVariable(m_Model, TextShadowColor);		
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _TextShadowColor.GetFloat(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOpacity", "" + sender, args.ToStr());

		_TextShadowOpacity.SetFloat(_UIWidget.GetTextShadowOpacity());
		_TextShadowOpacity.ToVariable(m_Model, TextShadowOpacity);
	}

	void OnModel_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOpacity", "" + sender, args.ToStr());

		_TextShadowOpacity.FromVariable(m_Model, TextShadowOpacity);		
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _TextShadowOpacity.GetFloat(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetX", "" + sender, args.ToStr());

		_TextShadowOffsetX.SetFloat(_UIWidget.GetTextShadowOffsetX());
		_TextShadowOffsetX.ToVariable(m_Model, TextShadowOffsetX);
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetX", "" + sender, args.ToStr());

		_TextShadowOffsetX.FromVariable(m_Model, TextShadowOffsetX);		
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _TextShadowOffsetX.GetFloat(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextShadowOffsetY", "" + sender, args.ToStr());

		_TextShadowOffsetY.SetFloat(_UIWidget.GetTextShadowOffsetY());
		_TextShadowOffsetY.ToVariable(m_Model, TextShadowOffsetY);
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextShadowOffsetY", "" + sender, args.ToStr());

		_TextShadowOffsetY.FromVariable(m_Model, TextShadowOffsetY);		
		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _TextShadowOffsetY.GetFloat());
	}

	void OnView_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextItalic", "" + sender, args.ToStr());

		_TextItalic.SetBool(_UIWidget.GetTextItalic());
		_TextItalic.ToVariable(m_Model, TextItalic);
	}

	void OnModel_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextItalic", "" + sender, args.ToStr());

		_TextItalic.FromVariable(m_Model, TextItalic);
		_UIWidget.SetTextItalic(_TextItalic.GetBool());
	}

	void OnView_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_TextBold", "" + sender, args.ToStr());

		_TextBold.SetBool(_UIWidget.GetTextBold());
		_TextBold.ToVariable(m_Model, TextBold);
	}

	void OnModel_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_TextBold", "" + sender, args.ToStr());

		_TextBold.FromVariable(m_Model, TextBold);
		_UIWidget.SetTextBold(_TextBold.GetBool());
	}
};
