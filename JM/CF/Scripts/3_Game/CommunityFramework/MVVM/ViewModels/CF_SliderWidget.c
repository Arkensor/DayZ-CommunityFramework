class CF_SliderWidget : CF_UIWidget
{
	reference string Min;
	reference string Max;
	reference string Current;

	protected SliderWidget _SliderWidget;
	protected CF_MVVM_PropertyBase _Min = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Max = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Current = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(Min, "Min");
		AddProperty(Max, "Max");
		AddProperty(Current, "Current");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SliderWidget, w);
	}

	void OnView_Min(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Min").Add(sender).Add(args);
#endif

		_Min.SetInt(_SliderWidget.GetMin());
	}

	void OnModel_Min(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Min").Add(sender).Add(args);
#endif

		//OnView_Min(m_Model, args);
	}

	void OnView_Max(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Max").Add(sender).Add(args);
#endif

		_Max.SetInt(_SliderWidget.GetMax());
	}

	void OnModel_Max(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Max").Add(sender).Add(args);
#endif

		//OnView_Max(m_Model, args);
	}

	void OnView_Current(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Current").Add(sender).Add(args);
#endif

		_Current.SetFloat(_SliderWidget.GetCurrent());
	}

	void OnModel_Current(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Current").Add(sender).Add(args);
#endif

		_SliderWidget.SetCurrent(_Current.GetFloat());
	}

	override bool WhatChanged(out string name, out string variable)
	{
		name = "Current";
		variable = Current;
		return true;
	}
};
