class CF_SpacerWidget : CF_SpacerBaseWidget
{
	reference string ContentAlignmentHorizontal;
	reference string ContentAlignmentVertical;

	protected SpacerWidget _SpacerWidget;
	protected CF_MVVM_PropertyBase _ContentAlignmentHorizontal = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _ContentAlignmentVertical = CF_MVVM_GetDefaultProperty();
	
	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();

		AddProperty(ContentAlignmentHorizontal, "ContentAlignmentHorizontal");
		AddProperty(ContentAlignmentVertical, "ContentAlignmentVertical");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerWidget, w);
	}

	void OnView_ContentAlignmentHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ContentAlignmentHorizontal").Add(sender).Add(args);
		#endif

		int _contentAlignmentH = _SpacerWidget.GetContentAlignmentH();
		EnScript.SetClassVar(m_Model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
	}

	void OnModel_ContentAlignmentHorizontal(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ContentAlignmentHorizontal").Add(sender).Add(args);
		#endif

		int _contentAlignmentH;
		EnScript.GetClassVar(m_Model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
		_SpacerWidget.SetContentAlignmentH(_contentAlignmentH);
	}

	void OnView_ContentAlignmentVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_ContentAlignmentVertical").Add(sender).Add(args);
		#endif

		int _contentAlignmentV = _SpacerWidget.GetContentAlignmentV();
		EnScript.SetClassVar(m_Model, ContentAlignmentVertical, 0, _contentAlignmentV);
	}

	void OnModel_ContentAlignmentVertical(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_ContentAlignmentVertical").Add(sender).Add(args);
		#endif

		int _contentAlignmentV;
		EnScript.GetClassVar(m_Model, ContentAlignmentVertical, 0, _contentAlignmentV);
		_SpacerWidget.SetContentAlignmentV(_contentAlignmentV);
	}
};
