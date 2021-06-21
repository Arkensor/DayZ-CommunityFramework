class CF_BaseListboxWidget : CF_UIWidget
{
	reference string NumberItems;
	reference string Selected;

	protected BaseListboxWidget _BaseListboxWidget;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_BaseListboxWidget, w);
	}
	
	void OnView_NumberItems(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, NumberItems, 0, _BaseListboxWidget.GetNumItems());
	}

	void OnModel_NumberItems(CF_Model_Base model)
	{
		OnView_NumberItems(model);
	}

	void OnView_Selected(CF_Model_Base model)
	{
		int _value = _BaseListboxWidget.GetSelectedRow();
		EnScript.SetClassVar(model, Selected, 0, _value);
	}

	void OnModel_Selected(CF_Model_Base model)
	{
		int _value;
		EnScript.GetClassVar(model, Selected, 0, _value);
		_BaseListboxWidget.SelectRow(_value);
	}
};
