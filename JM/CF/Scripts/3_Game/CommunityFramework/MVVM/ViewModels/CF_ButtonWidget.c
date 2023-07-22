class CF_ButtonWidget : CF_UIWidget
{
	reference string State;
	reference string Text;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextHorizontalAlignment;
	reference string TextVerticalAlignment;
	reference string TextProportion;

	protected ButtonWidget _ButtonWidget;
	protected CF_MVVM_PropertyBase _State = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Text = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextHorizontalAlignment = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextVerticalAlignment = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextProportion = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(State, "State");
		AddProperty(Text, "Text");
		AddProperty(TextOffsetX, "TextOffsetX");
		AddProperty(TextOffsetY, "TextOffsetY");
		AddProperty(TextHorizontalAlignment, "TextHorizontalAlignment");
		AddProperty(TextVerticalAlignment, "TextVerticalAlignment");
		AddProperty(TextProportion, "TextProportion");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ButtonWidget, w);
	}

	void OnView_State(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_State").Add(sender).Add(args);
#endif

		_State.SetBool(_ButtonWidget.GetState());
	}

	void OnModel_State(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_State").Add(sender).Add(args);
#endif

		_ButtonWidget.SetState(_State.GetBool());
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_Text").Add(sender).Add(args);
#endif
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_Text").Add(sender).Add(args);
#endif

		_ButtonWidget.SetText(_Text.GetString());
	}

	void OnView_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextOffsetX").Add(sender).Add(args);
#endif
	}

	void OnModel_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextOffsetX").Add(sender).Add(args);
#endif

		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextOffsetY").Add(sender).Add(args);
#endif
	}

	void OnModel_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextOffsetY").Add(sender).Add(args);
#endif

		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextHorizontalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextHorizontalAlignment").Add(sender).Add(args);
#endif
	}

	void OnModel_TextHorizontalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextHorizontalAlignment").Add(sender).Add(args);
#endif

		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment.GetInt());
	}

	void OnView_TextVerticalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextVerticalAlignment").Add(sender).Add(args);
#endif
	}

	void OnModel_TextVerticalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextVerticalAlignment").Add(sender).Add(args);
#endif

		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment.GetInt());
	}

	void OnView_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnView_TextProportion").Add(sender).Add(args);
#endif

		_TextProportion.SetInt(_ButtonWidget.GetTextProportion());
	}

	void OnModel_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "OnModel_TextProportion").Add(sender).Add(args);
#endif

		_ButtonWidget.SetTextProportion(_TextProportion.GetInt());
	}

	override bool WhatChanged(out string name, out string variable)
	{
		name = "State";
		variable = State;
		return true;
	}
};
