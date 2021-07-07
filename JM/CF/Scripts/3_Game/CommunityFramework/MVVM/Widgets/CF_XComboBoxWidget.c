class CF_XComboBoxWidget : CF_UIWidget
{
	reference string Selected;
	reference string Items;

	protected XComboBoxWidget _XComboBoxWidget;
	protected ref CF_ObservableCollection _Items;
	protected CF_TypeConverter _Selected;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Selected, "Selected");
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_XComboBoxWidget, w);
	}

	void OnView_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Selected", "" + model, evt.String());

		int _value = _XComboBoxWidget.GetCurrentItem();
		EnScript.SetClassVar(model, Selected, 0, _value);
	}

	void OnModel_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Selected", "" + model, evt.String());

		int _value;
		EnScript.GetClassVar(model, Selected, 0, _value);
		_XComboBoxWidget.SetCurrentItem(_value);
	}

	void OnView_Items(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Items", "" + model, evt.String());

		EnScript.SetClassVar(model, Items, 0, _Items);
	}

	void OnModel_Items(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Items", "" + model, evt.String());

		EnScript.GetClassVar(model, Items, 0, _Items);

		int selected = _XComboBoxWidget.GetCurrentItem();

		_XComboBoxWidget.ClearAll();
		for (int i = 0; i < _Items.Count(); i++)
		{
			_XComboBoxWidget.AddItem(_Items.GetConverter(i).GetString());
		}

		_XComboBoxWidget.SetCurrentItem(selected);

		NotifyPropertyChanged("Selected");
	}
};
