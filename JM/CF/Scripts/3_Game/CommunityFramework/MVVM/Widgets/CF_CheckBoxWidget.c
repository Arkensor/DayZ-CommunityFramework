class CF_CheckBoxWidget : CF_UIWidget
{
	reference string Text;
	reference string Checked;

	protected CheckBoxWidget _CheckBoxWidget;
	protected string _Text;
	protected bool _Checked;

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
		
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.SetString(_Text);
		pType.ToVariable(model, Text);
	}

	void OnModel_Text(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Text", "" + model, evt.String());
		
		auto pType = CF.MVVM.GetPropertyType(model, Text);
		pType.FromVariable(model, Text);
		_CheckBoxWidget.SetText(pType.GetString());
	}

	void OnView_Checked(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Checked", "" + model, evt.String());
		
		EnScript.SetClassVar(model, Checked, 0, _Checked);
	}

	void OnModel_Checked(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Checked", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Checked, 0, _Checked);
		_CheckBoxWidget.SetChecked(_Checked);
	}

	override bool OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());

		if (evt.Continue)
		{
			_Checked = _CheckBoxWidget.IsChecked();
		}

		NotifyPropertyChanged("Checked");

		return true;
	}
};
