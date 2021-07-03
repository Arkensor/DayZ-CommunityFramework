class CF_EditBoxWidget : CF_UIWidget
{
	reference string Text;

	protected EditBoxWidget _EditBoxWidget;
	protected string _Text;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Text, "Text");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_EditBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.SetString(_EditBoxWidget.GetText());
		pType.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.FromVariable(model, Text);
		_Text = pType.GetString();
		_EditBoxWidget.SetText(_Text);
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (!evt.Continue)
		{
			_EditBoxWidget.SetText(_Text);
		}

		_Text = _EditBoxWidget.GetText();
		NotifyPropertyChanged("Text");

		return true;
	}
};
