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
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(Checked, "Checked");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		#endif
		
		_CheckBoxWidget.SetText(_Text.GetString());
	}

	void OnView_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Checked", "" + sender, args.ToStr());
		#endif
		
		_Checked.SetBool(_CheckBoxWidget.IsChecked());
	}

	void OnModel_Checked(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Checked", "" + sender, args.ToStr());
		#endif
		
		_CheckBoxWidget.SetChecked(_Checked.GetBool());
	}

	/*
	 * @note Prevent input in OnMouseButtonDown by setting Continue to false.
	 */
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", "" + w);
		#endif
		
		NotifyPropertyChanged(Checked, "Checked");
		
		return super.OnChange(w, x, y, finished);
	}
};
