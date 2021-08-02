class CF_EditBoxWidget : CF_UIWidget
{
	reference string Text;

	protected EditBoxWidget _EditBoxWidget;
	protected ref CF_TypeConverter _Text = CF_GetDefaultTC();

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Text, "Text");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_EditBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		
		_Text.SetString(_EditBoxWidget.GetText());
		_Text.ToVariable(m_Model, Text);
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		
		_Text.FromVariable(m_Model, Text);
		_EditBoxWidget.SetText(_Text.GetString());
	}

	override bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
		CF_Trace trace(this, "OnChange", args.ToStr());

		if (!args.Continue)
		{
			_EditBoxWidget.SetText(_Text.GetString());
		}

		NotifyPropertyChanged(Text, "Text");

		return true;
	}
};
