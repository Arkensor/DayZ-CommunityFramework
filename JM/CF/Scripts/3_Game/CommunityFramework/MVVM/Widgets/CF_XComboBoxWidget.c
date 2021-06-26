class CF_XComboBoxWidget : CF_UIWidget
{
	reference string Selected;
	reference string Items;

	protected XComboBoxWidget _XComboBoxWidget;
	protected ref array<string> _Items = new array<string>();

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Selected, "Selected");
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_XComboBoxWidget, w);
	}

	void OnView_Selected(CF_ModelBase model, CF_Event evt)
	{
		int _value = _XComboBoxWidget.GetCurrentItem();
		EnScript.SetClassVar(model, Selected, 0, _value);
	}

	void OnModel_Selected(CF_ModelBase model, CF_Event evt)
	{
		int _value;
		EnScript.GetClassVar(model, Selected, 0, _value);
		_XComboBoxWidget.SetCurrentItem(_value);
	}

	void OnView_Items(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, Items, 0, _Items);
	}

	void OnModel_Items(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, Items, 0, _Items);

		_XComboBoxWidget.ClearAll();
		for (int i = 0; i < _Items.Count(); i++)
		{
			_XComboBoxWidget.AddItem(_Items[i]);
		}
	}
};
