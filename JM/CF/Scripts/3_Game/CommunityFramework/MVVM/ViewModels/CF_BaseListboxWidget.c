class CF_BaseListboxWidget : CF_UIWidget
{
	reference string NumberItems;
	reference string Selected;

	protected BaseListboxWidget _BaseListboxWidget;
	protected CF_MVVM_PropertyBase _NumberItems = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Selected = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(NumberItems, "NumberItems");
		AddProperty(Selected, "Selected");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_BaseListboxWidget, w);
	}

	void OnView_NumberItems(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_NumberItems").Add(sender).Add(args);
#endif

		_NumberItems.SetInt(_BaseListboxWidget.GetNumItems());
	}

	void OnModel_NumberItems(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_NumberItems").Add(sender).Add(args);
#endif

		OnView_NumberItems(m_Model, args);
	}

	void OnView_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Selected").Add(sender).Add(args);
#endif

		_Selected.SetInt(_BaseListboxWidget.GetSelectedRow());
	}

	void OnModel_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Selected").Add(sender).Add(args);
#endif

		_BaseListboxWidget.SelectRow(_Selected.GetInt());
	}
};
