class CF_HtmlWidget : CF_TextWidget
{
	reference string File;

	protected HtmlWidget _HtmlWidget;
	protected CF_TypeConverter _File = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(File, "File");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_HtmlWidget, w);
	}

	void OnView_File(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_File", "" + sender, args.ToStr());
		
		_File.ToVariable(m_Model, File);
	}

	void OnModel_File(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_File", "" + sender, args.ToStr());
		
		_File.FromVariable(m_Model, File);
		_HtmlWidget.LoadFile(_File.GetString());
	}
};
