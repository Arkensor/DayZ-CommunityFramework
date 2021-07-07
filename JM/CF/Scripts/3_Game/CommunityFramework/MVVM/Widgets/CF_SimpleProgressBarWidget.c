class CF_SimpleProgressBarWidget : CF_UIWidget
{
	reference string Min;
	reference string Max;
	reference string Current;

	protected SimpleProgressBarWidget _SimpleProgressBarWidget;
	protected CF_TypeConverter _Min;
	protected CF_TypeConverter _Max;
	protected CF_TypeConverter _Current;

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
		Class.CastTo(_SimpleProgressBarWidget, w);
	}
	
	void OnView_Min(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Min", "" + model, evt.String());

		EnScript.SetClassVar(model, Min, 0, _SimpleProgressBarWidget.GetMin());
	}

	void OnModel_Min(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Min", "" + model, evt.String());

		OnView_Min(model, evt);
	}

	void OnView_Max(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Max", "" + model, evt.String());

		EnScript.SetClassVar(model, Max, 0, _SimpleProgressBarWidget.GetMax());
	}

	void OnModel_Max(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Max", "" + model, evt.String());

		OnView_Max(model, evt);
	}

	void OnView_Current(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Current", "" + model, evt.String());

		float _value = _SimpleProgressBarWidget.GetCurrent();
		EnScript.SetClassVar(model, Current, 0, _value);
	}

	void OnModel_Current(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Current", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, Current, 0, _value);
		_SimpleProgressBarWidget.SetCurrent(_value);
	}
};
