class CF_SimpleProgressBarWidget : CF_UIWidget
{
	reference string Min;
	reference string Max;
	reference string Current;

	protected SimpleProgressBarWidget _SimpleProgressBarWidget;
	protected CF_MVVM_PropertyBase _Min = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Max = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Current = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Min, "Min");
		AddProperty(Max, "Max");
		AddProperty(Current, "Current");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SimpleProgressBarWidget, w);
	}
	
	void OnView_Min(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Min").Add(sender).Add(args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, Min, 0, _SimpleProgressBarWidget.GetMin());
	}

	void OnModel_Min(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Min").Add(sender).Add(args.ToStr());
		#endif

		OnView_Min(m_Model, args);
	}

	void OnView_Max(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Max").Add(sender).Add(args.ToStr());
		#endif

		EnScript.SetClassVar(m_Model, Max, 0, _SimpleProgressBarWidget.GetMax());
	}

	void OnModel_Max(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Max").Add(sender).Add(args.ToStr());
		#endif

		OnView_Max(m_Model, args);
	}

	void OnView_Current(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Current").Add(sender).Add(args.ToStr());
		#endif

		float _value = _SimpleProgressBarWidget.GetCurrent();
		EnScript.SetClassVar(m_Model, Current, 0, _value);
	}

	void OnModel_Current(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Current").Add(sender).Add(args.ToStr());
		#endif

		float _value;
		EnScript.GetClassVar(m_Model, Current, 0, _value);
		_SimpleProgressBarWidget.SetCurrent(_value);
	}
};
