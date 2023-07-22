class CF_ScrollWidget : CF_SpacerBaseWidget
{
	reference string ScrollbarWidth;
	reference string ContentWidth;
	reference string ContentHeight;
	reference string HorizontalScrollPosition;
	reference string VerticalScrollPosition;
	reference string HorizontalScrollStep;
	reference string VerticalScrollStep;

	protected ScrollWidget _ScrollWidget;
	protected CF_MVVM_PropertyBase _ScrollbarWidth = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ContentWidth = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ContentHeight = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _HorizontalScrollPosition = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _VerticalScrollPosition = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _HorizontalScrollStep = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _VerticalScrollStep = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(ScrollbarWidth, "ScrollbarWidth");
		AddProperty(ContentWidth, "ContentWidth");
		AddProperty(ContentHeight, "ContentHeight");
		AddProperty(HorizontalScrollPosition, "HorizontalScrollPosition");
		AddProperty(VerticalScrollPosition, "VerticalScrollPosition");
		AddProperty(HorizontalScrollStep, "HorizontalScrollStep");
		AddProperty(VerticalScrollStep, "VerticalScrollStep");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ScrollWidget, w);
	}

	void OnView_ScrollbarWidth(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_ScrollbarWidth").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, ScrollbarWidth, 0, _ScrollWidget.GetScrollbarWidth());
	}

	void OnModel_ScrollbarWidth(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_ScrollbarWidth").Add(sender).Add(args);
#endif

		OnView_ScrollbarWidth(m_Model, args);
	}

	void OnView_ContentWidth(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_ContentWidth").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, ContentWidth, 0, _ScrollWidget.GetContentWidth());
	}

	void OnModel_ContentWidth(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_ContentWidth").Add(sender).Add(args);
#endif

		OnView_ContentWidth(m_Model, args);
	}

	void OnView_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_ContentHeight").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, ContentHeight, 0, _ScrollWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_ContentHeight").Add(sender).Add(args);
#endif

		OnView_ContentHeight(m_Model, args);
	}

	void OnView_HorizontalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_HorizontalScrollPosition").Add(sender).Add(args);
#endif

		float _value = _ScrollWidget.GetHScrollPos();
		EnScript.SetClassVar(m_Model, HorizontalScrollPosition, 0, _value);
	}

	void OnModel_HorizontalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_HorizontalScrollPosition").Add(sender).Add(args);
#endif

		float _value;
		EnScript.GetClassVar(m_Model, HorizontalScrollPosition, 0, _value);
		_ScrollWidget.HScrollToPos(_value);
	}

	void OnView_VerticalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_VerticalScrollPosition").Add(sender).Add(args);
#endif

		float _value = _ScrollWidget.GetVScrollPos();
		EnScript.SetClassVar(m_Model, VerticalScrollPosition, 0, _value);
	}

	void OnModel_VerticalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_VerticalScrollPosition").Add(sender).Add(args);
#endif

		float _value;
		EnScript.GetClassVar(m_Model, VerticalScrollPosition, 0, _value);
		_ScrollWidget.VScrollToPos(_value);
	}

	void OnView_HorizontalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_HorizontalScrollStep").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, HorizontalScrollStep, 0, _HorizontalScrollStep);
	}

	void OnModel_HorizontalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_HorizontalScrollStep").Add(sender).Add(args);
#endif

		EnScript.GetClassVar(m_Model, HorizontalScrollStep, 0, _HorizontalScrollStep);
		//_ScrollWidget.HScrollStep(_HorizontalScrollStep);
	}

	void OnView_VerticalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_VerticalScrollStep").Add(sender).Add(args);
#endif

		EnScript.SetClassVar(m_Model, VerticalScrollStep, 0, _VerticalScrollStep);
	}

	void OnModel_VerticalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_VerticalScrollStep").Add(sender).Add(args);
#endif

		EnScript.GetClassVar(m_Model, VerticalScrollStep, 0, _VerticalScrollStep);
		//_ScrollWidget.VScrollStep(_VerticalScrollStep);
	}
};
