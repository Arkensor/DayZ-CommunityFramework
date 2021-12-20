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
	protected CF_MVVM_PropertyBase _TextColor = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOutlineSize = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOutlineColor = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowSize = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowColor = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOpacity = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOffsetX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextShadowOffsetY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextItalic = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextBold = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

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
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_UIWidget, w);
	}

	void OnView_TextColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextColor").Add(sender).Add(args);
#endif

		OnModel_TextColor(sender, args);
	}

	void OnModel_TextColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextColor").Add(sender).Add(args);
#endif

		_UIWidget.SetTextColor(_TextColor.GetInt());
	}

	void OnView_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextOutlineSize").Add(sender).Add(args);
#endif

		_TextOutlineSize.SetFloat(_UIWidget.GetTextOutlineSize());
	}

	void OnModel_TextOutlineSize(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextOutlineSize").Add(sender).Add(args);
#endif

		_UIWidget.SetTextOutline(_TextOutlineSize.GetFloat(), _UIWidget.GetTextOutlineColor());
	}

	void OnView_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextOutlineColor").Add(sender).Add(args);
#endif

		_TextOutlineColor.SetFloat(_UIWidget.GetTextOutlineColor());
	}

	void OnModel_TextOutlineColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextOutlineColor").Add(sender).Add(args);
#endif

		_UIWidget.SetTextOutline(_UIWidget.GetTextOutlineSize(), _TextOutlineColor.GetFloat());
	}

	void OnView_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextShadowSize").Add(sender).Add(args);
#endif

		_TextShadowSize.SetFloat(_UIWidget.GetTextShadowSize());
	}

	void OnModel_TextShadowSize(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextShadowSize").Add(sender).Add(args);
#endif

		_UIWidget.SetTextShadow(_TextShadowSize.GetFloat(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextShadowColor").Add(sender).Add(args);
#endif

		_TextShadowColor.SetFloat(_UIWidget.GetTextShadowColor());
	}

	void OnModel_TextShadowColor(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextShadowColor").Add(sender).Add(args);
#endif

		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _TextShadowColor.GetFloat(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextShadowOpacity").Add(sender).Add(args);
#endif

		_TextShadowOpacity.SetFloat(_UIWidget.GetTextShadowOpacity());
	}

	void OnModel_TextShadowOpacity(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOpacity").Add(sender).Add(args);
#endif

		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _TextShadowOpacity.GetFloat(), _UIWidget.GetTextShadowOffsetX(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextShadowOffsetX").Add(sender).Add(args);
#endif

		_TextShadowOffsetX.SetFloat(_UIWidget.GetTextShadowOffsetX());
	}

	void OnModel_TextShadowOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOffsetX").Add(sender).Add(args);
#endif

		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _TextShadowOffsetX.GetFloat(), _UIWidget.GetTextShadowOffsetY());
	}

	void OnView_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextShadowOffsetY").Add(sender).Add(args);
#endif

		_TextShadowOffsetY.SetFloat(_UIWidget.GetTextShadowOffsetY());
	}

	void OnModel_TextShadowOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextShadowOffsetY").Add(sender).Add(args);
#endif

		_UIWidget.SetTextShadow(_UIWidget.GetTextShadowSize(), _UIWidget.GetTextShadowColor(), _UIWidget.GetTextShadowOpacity(), _UIWidget.GetTextShadowOffsetX(), _TextShadowOffsetY.GetFloat());
	}

	void OnView_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextItalic").Add(sender).Add(args);
#endif

		_TextItalic.SetBool(_UIWidget.GetTextItalic());
	}

	void OnModel_TextItalic(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextItalic").Add(sender).Add(args);
#endif

		_UIWidget.SetTextItalic(_TextItalic.GetBool());
	}

	void OnView_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextBold").Add(sender).Add(args);
#endif

		_TextBold.SetBool(_UIWidget.GetTextBold());
	}

	void OnModel_TextBold(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextBold").Add(sender).Add(args);
#endif

		_UIWidget.SetTextBold(_TextBold.GetBool());
	}
};
