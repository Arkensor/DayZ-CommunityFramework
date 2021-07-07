class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected CF_TypeConverter _Text;
	protected CF_TypeConverter _Checked;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Text, "Text");
		AddProperty(Checked, "Checked");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_CheckBoxWidget, w);
	}

	void OnView_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Text", "" + model, evt.String());
		
		_Text.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());
		
		_Text.FromVariable(model, Text);
		_CheckBoxWidget.SetText(_Text.GetString());
	}

	void OnView_Checked(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Checked", "" + model, evt.String());
		
		_Checked.SetBool(_CheckBoxWidget.IsChecked());
		_Checked.ToVariable(model, Checked);
	}

	void OnModel_Checked(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Checked", "" + model, evt.String());
		
		_Checked.FromVariable(model, Checked);
		_CheckBoxWidget.SetChecked(_Checked.GetBool());
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (!evt.Continue)
		{
			_CheckBoxWidget.SetChecked(!_CheckBoxWidget.IsChecked());
		}

		return true;
	}
};
