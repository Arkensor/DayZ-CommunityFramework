class CF_RichTextWidget : CF_TextWidget
{
	reference string ContentHeight;
	reference string ContentOffset;
	reference string ContentSnapToLine;
	reference string LineWidths;

	protected RichTextWidget _RichTextWidget;
	protected CF_MVVM_PropertyBase _ContentHeight = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ContentOffset = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ContentSnapToLine = CF_MVVM_GetDefaultProperty();
	protected CF_ObservableCollection _LineWidths;

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(ContentHeight, "ContentHeight");
		AddProperty(ContentOffset, "ContentOffset");
		AddProperty(ContentSnapToLine, "ContentSnapToLine");
		AddProperty(LineWidths, "LineWidths");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RichTextWidget, w);
	}

	override void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Text").Add(sender).Add(args);
		#endif

		super.OnModel_Text(sender, args);

		NotifyPropertyChanged(LineWidths, "LineWidths");
	}

	void OnView_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ContentHeight").Add(sender).Add(args);
		#endif

		_ContentHeight.SetFloat(_RichTextWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ContentHeight").Add(sender).Add(args);
		#endif

		OnView_ContentHeight(m_Model, args);
	}

	void OnView_ContentOffset(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ContentOffset").Add(sender).Add(args);
		#endif

		_ContentOffset.SetFloat(_RichTextWidget.GetContentOffset());
	}

	void OnModel_ContentOffset(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ContentOffset").Add(sender).Add(args);
		#endif

		_RichTextWidget.SetContentOffset(_ContentSnapToLine.GetFloat(), _ContentSnapToLine.GetBool());
	}

	void OnView_ContentSnapToLine(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ContentSnapToLine").Add(sender).Add(args);
		#endif

		OnModel_ContentSnapToLine(sender, args);
	}

	void OnModel_ContentSnapToLine(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ContentSnapToLine").Add(sender).Add(args);
		#endif

		_RichTextWidget.SetContentOffset(_ContentSnapToLine.GetFloat(), _ContentSnapToLine.GetBool());
	}

	void OnView_LineWidths(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_LineWidths").Add(sender).Add(args);
		#endif

		_LineWidths.Clear();
		for (int i = 0; i < _RichTextWidget.GetNumLines(); i++)
		{
			_LineWidths.InsertFloat(_RichTextWidget.GetLineWidth(i));
		}
	}

	void OnModel_LineWidths(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_LineWidths").Add(sender).Add(args);
		#endif

		OnView_LineWidths(m_Model, args);
	}
};
