class CF_EditBoxWidget : CF_UIWidget
{
	reference string Text;

	protected EditBoxWidget _EditBoxWidget;
	protected CF_MVVM_PropertyBase _Text = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Text, "Text");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_EditBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		#endif
		
		_Text.SetString(_EditBoxWidget.GetText());
		_Text.ToVariable(m_Model, Text);
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		#endif
		
		_Text.FromVariable(m_Model, Text);
		_EditBoxWidget.SetText(_Text.GetString());
	}

	override bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", args.ToStr());
		#endif

		if (!args.Continue)
		{
			_EditBoxWidget.SetText(_Text.GetString());
		}

		NotifyPropertyChanged(Text, "Text");

		return true;
	}
};
