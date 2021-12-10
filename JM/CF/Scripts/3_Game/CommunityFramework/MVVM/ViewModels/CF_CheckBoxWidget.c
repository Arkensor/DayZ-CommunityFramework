class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected CF_MVVM_PropertyBase _Text = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Checked = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(Checked, "Checked");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Text").Add(sender).Add(args);
		#endif
		
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Text").Add(sender).Add(args);
		#endif
		
		_CheckBoxWidget.SetText(_Text.GetString());
	}

	void OnView_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Checked").Add(sender).Add(args);
		#endif
		
		_Checked.SetBool(_CheckBoxWidget.IsChecked());
	}

	void OnModel_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Checked").Add(sender).Add(args);
		#endif
		
		_CheckBoxWidget.SetChecked(_Checked.GetBool());
	}

	override bool WhatChanged(out string name, out string variable)
	{
		name = "Checked";
		variable = Checked;
		return true;
	}
};
