class CF_HtmlWidget : CF_TextWidget
{
	reference string File;

	protected HtmlWidget _HtmlWidget;
	protected string _File;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(File, "File");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_HtmlWidget, w);
	}

	void OnView_File(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.SetClassVar(model, File, 0, _File);
	}

	void OnModel_File(CF_ModelBase model, CF_EventArgs evt)
	{
		EnScript.GetClassVar(model, File, 0, _File);
		_HtmlWidget.LoadFile(_File);
	}
};
