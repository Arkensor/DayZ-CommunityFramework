class CF_BaseListboxWidget : CF_UIWidget
{
	reference string NumberItems;
	reference string Selected;

	protected BaseListboxWidget _BaseListboxWidget;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(NumberItems, "NumberItems");
		AddProperty(Selected, "Selected");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_BaseListboxWidget, w);
	}
	
	void OnView_NumberItems(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_NumberItems", "" + model, evt.String());
		
		EnScript.SetClassVar(model, NumberItems, 0, _BaseListboxWidget.GetNumItems());
	}

	void OnModel_NumberItems(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_NumberItems", "" + model, evt.String());
		
		OnView_NumberItems(model, evt);
	}

	void OnView_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Selected", "" + model, evt.String());
		
		int _value = _BaseListboxWidget.GetSelectedRow();
		EnScript.SetClassVar(model, Selected, 0, _value);
	}

	void OnModel_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Selected", "" + model, evt.String());
		
		int _value;
		EnScript.GetClassVar(model, Selected, 0, _value);
		_BaseListboxWidget.SelectRow(_value);
	}
};
