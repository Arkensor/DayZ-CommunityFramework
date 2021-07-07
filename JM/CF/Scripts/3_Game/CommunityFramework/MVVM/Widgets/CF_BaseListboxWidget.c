class CF_BaseListboxWidget : CF_UIWidget
{
	reference string NumberItems;
	reference string Selected;

	protected BaseListboxWidget _BaseListboxWidget;
	protected CF_TypeConverter _NumberItems;
	protected CF_TypeConverter _Selected;

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
		
		_NumberItems.SetInt(_BaseListboxWidget.GetNumItems());
		_NumberItems.ToVariable(model, NumberItems);
	}

	void OnModel_NumberItems(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_NumberItems", "" + model, evt.String());
		
		OnView_NumberItems(model, evt);
	}

	void OnView_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Selected", "" + model, evt.String());
		
		_Selected.SetInt(_BaseListboxWidget.GetSelectedRow());
		_Selected.ToVariable(model, Selected);
	}

	void OnModel_Selected(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Selected", "" + model, evt.String());
		
		_Selected.FromVariable(model, Selected);
		_BaseListboxWidget.SelectRow(_Selected.GetInt());
	}
};
