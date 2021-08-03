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
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Selected, "Selected");
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_XComboBoxWidget, w);
	}

	void OnView_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Selected", "" + sender, args.ToStr());
		#endif

		_Selected.SetFloat(_XComboBoxWidget.GetCurrentItem());
	}

	void OnModel_Selected(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Selected", "" + sender, args.ToStr());
		#endif

		_XComboBoxWidget.SetCurrentItem(_Selected.GetFloat());
	}

	void OnView_Items(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Items", "" + sender, args.ToStr());
		#endif

		OnModel_Items(sender, args);
	}

	void OnModel_Items(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Items", "" + sender, args.ToStr());
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
