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
		auto trace = CF_Trace_0(this, "GetProperties");
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
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Text").Add(sender).Add(args.ToStr());
		#endif

		OnModel_Text(sender, args);
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Text").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetText(_Text.GetString());
	}

	void OnView_TextSpacingHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextSpacingHorizontal").Add(sender).Add(args.ToStr());
		#endif

		OnModel_TextSpacingHorizontal(sender, args);
	}

	void OnModel_TextSpacingHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextSpacingHorizontal").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextSpacing(_TextSpacingHorizontal.GetInt(), _TextSpacingVertical.GetInt());
	}

	void OnView_TextSpacingVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextSpacingVertical").Add(sender).Add(args.ToStr());
		#endif

		OnModel_TextSpacingVertical(sender, args);
	}

	void OnModel_TextSpacingVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextSpacingVertical").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextSpacing(_TextSpacingHorizontal.GetInt(), _TextSpacingVertical.GetInt());
	}

	void OnView_TextExactSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextExactSize").Add(sender).Add(args.ToStr());
		#endif

		OnModel_TextExactSize(sender, args);
	}

	void OnModel_TextExactSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextExactSize").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextExactSize(_TextExactSize.GetInt());
	}

	void OnView_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextOffsetX").Add(sender).Add(args.ToStr());
		#endif

		OnModel_TextOffsetX(sender, args);
	}

	void OnModel_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextOffsetX").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextOffset(_TextOffsetX.GetInt(), _TextOffsetY.GetInt());
	}

	void OnView_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextOffsetY").Add(sender).Add(args.ToStr());
		#endif

		OnModel_TextOffsetY(sender, args);
	}

	void OnModel_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextOffsetY").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextOffset(_TextOffsetX.GetInt(), _TextOffsetY.GetInt());
	}

	void OnView_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextOutlineSize").Add(sender).Add(args.ToStr());
		#endif

		_TextOutlineSize.SetInt(_TextWidget.GetOutlineSize());
	}

	void OnModel_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextOutlineSize").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetOutline(_TextOutlineSize.GetInt(), _TextWidget.GetOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextOutlineColor").Add(sender).Add(args.ToStr());
		#endif

		_TextOutlineColor.SetInt(_TextWidget.GetOutlineColor());
	}

	void OnModel_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextOutlineColor").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetOutline(_TextWidget.GetOutlineSize(), _TextOutlineColor.GetInt());
	}

	void OnView_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextShadowSize").Add(sender).Add(args.ToStr());
		#endif

		_TextShadowSize.SetFloat(_TextWidget.GetShadowSize());
	}

	void OnModel_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextShadowSize").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		_TextWidget.SetShadow(_TextShadowSize.GetInt(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextShadowColor").Add(sender).Add(args.ToStr());
		#endif

		_TextShadowColor.SetInt(_TextWidget.GetShadowColor());
	}

	void OnModel_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextShadowColor").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextShadowColor.GetInt(), _TextWidget.GetShadowOpacity(), _sx, _sy);
	}

	void OnView_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextShadowOpacity").Add(sender).Add(args.ToStr());
		#endif

		_TextShadowOpacity.SetFloat(_TextWidget.GetShadowOpacity());
	}

	void OnModel_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOpacity").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);
		
		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextShadowOpacity.GetFloat(), _sx, _sy);
	}

	void OnView_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextShadowOffsetX").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		_TextShadowOffsetX.SetFloat(_sx);
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOffsetX").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _TextShadowOffsetX.GetFloat(), _sy);
	}

	void OnView_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextShadowOffsetY").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		_TextShadowOffsetY.SetFloat(_sy);
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOffsetY").Add(sender).Add(args.ToStr());
		#endif

		float _sx, _sy;
		_TextWidget.GetShadowOffset(_sx, _sy);

		_TextWidget.SetShadow(_TextWidget.GetShadowSize(), _TextWidget.GetShadowColor(), _TextWidget.GetShadowOpacity(), _sx, _TextShadowOffsetY.GetFloat());
	}

	void OnView_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextItalic").Add(sender).Add(args.ToStr());
		#endif

		_TextItalic.SetBool(_TextWidget.GetItalic());
	}

	void OnModel_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextItalic").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetItalic(_TextItalic.GetBool());
	}

	void OnView_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextBold").Add(sender).Add(args.ToStr());
		#endif

		_TextBold.SetBool(_TextWidget.GetBold());
	}

	void OnModel_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextBold").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetBold(_TextBold.GetBool());
	}

	void OnView_TextSizeX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextSizeX").Add(sender).Add(args.ToStr());
		#endif

		int _x, _y;
		_TextWidget.GetTextSize(_x, _y);
		_TextSizeX.SetInt(_x);
	}

	void OnModel_TextSizeX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextSizeX").Add(sender).Add(args.ToStr());
		#endif

		OnView_TextSizeX(m_Model, args);
	}

	void OnView_TextSizeY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextSizeY").Add(sender).Add(args.ToStr());
		#endif

		int _x, _y;
		_TextWidget.GetTextSize(_x, _y);
		_TextSizeY.SetInt(_y);
	}

	void OnModel_TextSizeY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextSizeY").Add(sender).Add(args.ToStr());
		#endif

		OnView_TextSizeY(m_Model, args);
	}

	void OnView_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_TextProportion").Add(sender).Add(args.ToStr());
		#endif

		_TextProportion.SetFloat(_TextWidget.GetTextProportion());
	}

	void OnModel_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_TextProportion").Add(sender).Add(args.ToStr());
		#endif

		_TextWidget.SetTextProportion(_TextProportion.GetFloat());
	}
};
