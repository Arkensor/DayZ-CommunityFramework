class CF_HtmlWidget : CF_TextWidget
{
	reference string File;

	protected HtmlWidget _HtmlWidget;
	protected CF_MVVM_PropertyBase _File = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(File, "File");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_HtmlWidget, w);
	}

	void OnView_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_File").Add(sender).Add(args.ToStr());
		#endif
		
	}

	void OnModel_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_File").Add(sender).Add(args.ToStr());
		#endif
		
		_HtmlWidget.LoadFile(_File.GetString());
	}
};
