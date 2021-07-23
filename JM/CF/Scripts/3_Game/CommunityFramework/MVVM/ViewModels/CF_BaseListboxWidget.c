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
	
	void OnView_NumberItems(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_NumberItems", "" + sender, args.ToStr());
		
		_NumberItems.SetInt(_BaseListboxWidget.GetNumItems());
		_NumberItems.ToVariable(m_Model, NumberItems);
	}

	void OnModel_NumberItems(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_NumberItems", "" + sender, args.ToStr());
		
		OnView_NumberItems(m_Model, args);
	}

	void OnView_Selected(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_Selected", "" + sender, args.ToStr());
		
		_Selected.SetInt(_BaseListboxWidget.GetSelectedRow());
		_Selected.ToVariable(m_Model, Selected);
	}

	void OnModel_Selected(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Selected", "" + sender, args.ToStr());
		
		_Selected.FromVariable(m_Model, Selected);
		_BaseListboxWidget.SelectRow(_Selected.GetInt());
	}
};
