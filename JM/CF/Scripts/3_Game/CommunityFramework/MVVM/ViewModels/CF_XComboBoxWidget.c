class CF_XComboBoxWidget : CF_UIWidget
{
	reference string Selected;
	reference string Items;

	protected XComboBoxWidget _XComboBoxWidget;
	protected CF_ObservableCollection _Items;
	protected CF_MVVM_PropertyBase _Selected = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(Selected, "Selected");
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_XComboBoxWidget, w);
	}

	void OnView_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Selected").Add(sender).Add(args);
#endif

		_Selected.SetFloat(_XComboBoxWidget.GetCurrentItem());
	}

	void OnModel_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Selected").Add(sender).Add(args);
#endif

		_XComboBoxWidget.SetCurrentItem(_Selected.GetFloat());
	}

	void OnView_Items(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Items").Add(sender).Add(args);
#endif

		OnModel_Items(sender, args);
	}

	void OnModel_Items(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Items").Add(sender).Add(args);
#endif

		int selected = _XComboBoxWidget.GetCurrentItem();

		_XComboBoxWidget.ClearAll();
		for (int i = 0; i < _Items.Count(); i++)
		{
			_XComboBoxWidget.AddItem(_Items.GetString(i));
		}

		_XComboBoxWidget.SetCurrentItem(selected);

		NotifyPropertyChanged(Selected, "Selected");
	}
};
