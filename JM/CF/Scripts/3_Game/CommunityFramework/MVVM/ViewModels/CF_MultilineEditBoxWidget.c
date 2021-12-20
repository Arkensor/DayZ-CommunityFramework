class CF_MultilineEditBoxWidget : CF_TextWidget
{
	reference string CarriageLine;
	reference string CarriagePosition;

	protected MultilineEditBoxWidget _MultilineEditBoxWidget;
	protected CF_MVVM_PropertyBase _CarriageLine = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _CarriagePosition = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(CarriageLine, "CarriageLine");
		AddProperty(CarriagePosition, "CarriagePosition");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MultilineEditBoxWidget, w);
	}

	override void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Text").Add(sender).Add(args);
#endif

		string value;
		_MultilineEditBoxWidget.GetText(value);
		_Text.SetString(value);
	}

	void OnView_CarriageLine(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_CarriageLine").Add(sender).Add(args);
#endif

		_CarriageLine.SetInt(_MultilineEditBoxWidget.GetCarriageLine());
	}

	void OnModel_CarriageLine(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_CarriageLine").Add(sender).Add(args);
#endif

		OnView_CarriageLine(m_Model, args);
	}

	void OnView_CarriagePosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_CarriagePosition").Add(sender).Add(args);
#endif

		_CarriagePosition.SetInt(_MultilineEditBoxWidget.GetCarriagePos());
	}

	void OnModel_CarriagePosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_CarriagePosition").Add(sender).Add(args);
#endif

		OnView_CarriagePosition(m_Model, args);
	}

	override bool WhatChanged(out string name, out string variable)
	{
		name = "Text";
		variable = Text;
		return true;
	}
};
