class CF_HtmlWidget : CF_TextWidget
{
	reference string File;

	protected HtmlWidget _HtmlWidget;
	protected CF_TypeConverter _File;

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

	void OnView_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_File", "" + model, evt.String());
		
		_File.ToVariable(model, File);
	}

	void OnModel_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_File", "" + model, evt.String());
		
		_File.FromVariable(model, File);
		_HtmlWidget.LoadFile(_File.GetString());
	}
};
