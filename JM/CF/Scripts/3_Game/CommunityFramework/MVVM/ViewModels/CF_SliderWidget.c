class CF_SliderWidget : CF_UIWidget
{
	reference string Min;
	reference string Max;
	reference string Current;
	
	protected SliderWidget _SliderWidget;
	protected CF_TypeConverter _Min = CF_GetDefaultTC();
	protected CF_TypeConverter _Max = CF_GetDefaultTC();
	protected CF_TypeConverter _Current = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Min, "Min");
		AddProperty(Max, "Max");
		AddProperty(Current, "Current");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SliderWidget, w);
	}
	
	void OnView_Min(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Min", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, Min, 0, _SliderWidget.GetMin());
	}

	void OnModel_Min(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Min", "" + sender, args.ToStr());

		OnView_Min(m_Model, args);
	}

	void OnView_Max(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Max", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, Max, 0, _SliderWidget.GetMax());
	}

	void OnModel_Max(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Max", "" + sender, args.ToStr());

		OnView_Max(m_Model, args);
	}

	void OnView_Current(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Current", "" + sender, args.ToStr());

		float _value = _SliderWidget.GetCurrent();
		EnScript.SetClassVar(m_Model, Current, 0, _value);
	}

	void OnModel_Current(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Current", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, Current, 0, _value);
		_SliderWidget.SetCurrent(_value);
	}
};
