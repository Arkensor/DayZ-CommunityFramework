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
	protected CF_MVVM_PropertyBase _Text = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextSpacingHorizontal = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextSpacingVertical = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextExactSize = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOutlineSize = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOutlineColor = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowSize = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowColor = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOpacity = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOffsetX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOffsetY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextItalic = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextBold = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextSizeX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextSizeY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextProportion = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		#endif

		OnModel_Text(sender, args);
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		#endif

		_Text.FromVariable(m_Model, Text);
		_TextWidget.SetText(_Text.GetString());
	}

	void OnView_TextSpacingHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextSpacingHorizontal", "" + sender, args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
	}

	void OnModel_TextSpacingHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextSpacingHorizontal", "" + sender, args.ToStr());
		#endif

		EnScript.GetClassVar(m_Model, TextSpacingHorizontal, 0, _TextSpacingHorizontal);
		//_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextSpacingVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextSpacingVertical", "" + sender, args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, TextSpacingVertical, 0, _TextSpacingVertical);
	}

	void OnModel_TextSpacingVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextSpacingVertical", "" + sender, args.ToStr());
		#endif

		EnScript.GetClassVar(m_Model, TextSpacingVertical, 0, TextSpacingVertical);
		//_TextWidget.SetTextSpacing(_TextSpacingHorizontal, _TextSpacingVertical);
	}

	void OnView_TextExactSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextExactSize", "" + sender, args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, TextExactSize, 0, _TextExactSize);
	}

	void OnModel_TextExactSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextExactSize", "" + sender, args.ToStr());
		#endif

		EnScript.GetClassVar(m_Model, TextExactSize, 0, _TextExactSize);
		//_TextWidget.SetTextExactSize(_TextExactSize);
	}

	void OnView_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOffsetX", "" + sender, args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, TextOffsetX, 0, _TextOffsetX);
	}

	void OnModel_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOffsetX", "" + sender, args.ToStr());
		#endif

		EnScript.GetClassVar(m_Model, TextOffsetX, 0, _TextOffsetX);
		//_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOffsetY", "" + sender, args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, TextOffsetY, 0, _TextOffsetY);
	}

	void OnModel_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOffsetY", "" + sender, args.ToStr());
		#endif

		EnScript.GetClassVar(m_Model, TextOffsetY, 0, _TextOffsetY);
		//_TextWidget.SetShadow(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOutlineSize", "" + sender, args.ToStr());
		#endif

		float _value = _TextWidget.GetOutlineSize();
		EnScript.SetClassVar(m_Model, TextOutlineSize, 0, _value);
	}

	void OnModel_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOutlineSize", "" + sender, args.ToStr());
		#endif

		float _value;
		EnScript.GetClassVar(m_Model, TextOutlineSize, 0, _value);
		//_TextWidget.SetOutline(_value, _TextWidget.GetOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOutlineColor", "" + sender, args.ToStr());
		#endif

		float _value = _TextWidget.GetOutlineColor();
		EnScript.SetClassVar(m_Model, TextOutlineColor, 0, _value);
	}

	void OnModel_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOutlineColor", "" + sender, args.ToStr());
		#endif

		float _value;
		EnScript.GetClassVar(m_Model, TextOutlineColor, 0, _value);
		//_TextWidget.SetOutline(_TextWidget.GetOutlineSize(), _value);
	}

	void OnView_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextShadowSize", "" + sender, args.ToStr());
		#endif

		float _value = _TextWidget.GetShadowSize();
		EnScript.SetClassVar(m_Model, TextShadowSize, 0, _value);
	}

	void OnModel_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextShadowSize", "" + sender, args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(m_Model, TextShadowSize, 0, _value);
		//_TextWidget.SetShadow(_value, _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextShadowColor", "" + sender, args.ToStr());
		#endif

		float _value = _TextWidget.GetShadowColor();
		EnScript.SetClassVar(m_Model, TextShadowColor, 0, _value);
	}

	void OnModel_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextShadowColor", "" + sender, args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		float _value;
		EnScript.GetClassVar(m_Model, TextShadowColor, 0, _value);
		//_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _value, _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextShadowOpacity", "" + sender, args.ToStr());
		#endif

		float _value = _TextWidget.GetShadowOpacity();
		EnScript.SetClassVar(m_Model, TextShadowOpacity, 0, _value);
	}

	void OnModel_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextShadowOpacity", "" + sender, args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		float _value;
		EnScript.GetClassVar(m_Model, TextShadowOpacity, 0, _value);
		//_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _value, _sx, _sy);
	}

	void OnView_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextShadowOffsetX", "" + sender, args.ToStr());
		#endif

		float _value, _other;
		_TextWidget.GetShadowOffset(_value, _other);
		EnScript.SetClassVar(m_Model, TextShadowOffsetX, 0, _value);
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextShadowOffsetX", "" + sender, args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(m_Model, TextShadowOffsetX, 0, _sx);
		//_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextShadowOffsetY", "" + sender, args.ToStr());
		#endif

		float _value, _other;
		_TextWidget.GetShadowOffset(_other, _value);
		EnScript.SetClassVar(m_Model, TextShadowOffsetY, 0, _value);
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextShadowOffsetY", "" + sender, args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		EnScript.GetClassVar(m_Model, TextShadowOffsetY, 0, _sy);
		//_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextItalic", "" + sender, args.ToStr());
		#endif

		bool _value = _TextWidget.GetItalic();
		EnScript.SetClassVar(m_Model, TextItalic, 0, _value);
	}

	void OnModel_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextItalic", "" + sender, args.ToStr());
		#endif

		bool _value;
		EnScript.GetClassVar(m_Model, TextItalic, 0, _value);
		//_TextWidget.SetItalic(_value);
	}

	void OnView_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextBold", "" + sender, args.ToStr());
		#endif

		bool _value = _TextWidget.GetBold();
		EnScript.SetClassVar(m_Model, TextBold, 0, _value);
	}

	void OnModel_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextBold", "" + sender, args.ToStr());
		#endif

		bool _value;
		EnScript.GetClassVar(m_Model, TextBold, 0, _value);
		//_TextWidget.SetBold(_value);
	}

	void OnView_TextSizeX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextSizeX", "" + sender, args.ToStr());
		#endif

		int _value, _other;
		_TextWidget.GetTextSize(_value, _other);
		EnScript.SetClassVar(m_Model, TextSizeX, 0, _value);
	}

	void OnModel_TextSizeX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextSizeX", "" + sender, args.ToStr());
		#endif

		OnView_TextSizeX(m_Model, args);
	}

	void OnView_TextSizeY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextSizeY", "" + sender, args.ToStr());
		#endif

		int _value, _other;
		_TextWidget.GetTextSize(_other, _value);
		EnScript.SetClassVar(m_Model, TextSizeY, 0, _value);
	}

	void OnModel_TextSizeY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextSizeY", "" + sender, args.ToStr());
		#endif

		OnView_TextSizeY(m_Model, args);
	}

	void OnView_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextProportion", "" + sender, args.ToStr());
		#endif

		bool _value = _TextWidget.GetTextProportion();
		EnScript.SetClassVar(m_Model, TextProportion, 0, _value);
	}

	void OnModel_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextProportion", "" + sender, args.ToStr());
		#endif

		bool _value;
		EnScript.GetClassVar(m_Model, TextProportion, 0, _value);
		_TextWidget.SetTextProportion(_value);
	}
};
