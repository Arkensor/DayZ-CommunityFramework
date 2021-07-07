class CF_EditBoxWidget : CF_UIWidget
{
	reference string Text;

	protected EditBoxWidget _EditBoxWidget;
	protected CF_TypeConverter _Text;

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

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());
		
		_Text.SetString(_EditBoxWidget.GetText());
		_Text.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());
		
		_Text.FromVariable(model, Text);
		_EditBoxWidget.SetText(_Text.GetString());
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (!evt.Continue)
		{
			_EditBoxWidget.SetText(_Text.GetString());
		}

		NotifyPropertyChanged("Text");

		return true;
	}
};
