class CF_TextListboxItem : CF_ModelBase
{
	string Text;
	Class Data;
	int Color;
};

class CF_TextListboxWidget : CF_BaseListboxWidget
{
	reference string Items;

	protected TextListboxWidget _TextListboxWidget;
	protected ref CF_ObservableCollection _Items;

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextListboxWidget, w);
	}

	void OnView_Items(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Items").Add(sender).Add(args);
		#endif

		EnScript.SetClassVar(m_Model, Items, 0, _Items);
	}

	void OnModel_Items(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Items").Add(sender).Add(args);
		#endif

		EnScript.GetClassVar(m_Model, Items, 0, _Items);

		CF_TextListboxItem selectedItem;
		int selectedRow = _TextListboxWidget.GetSelectedRow();
		if (selectedRow != -1)
		{
			_TextListboxWidget.GetItemData(selectedRow, 0, selectedItem);
		}

		selectedRow = -1;

		_TextListboxWidget.ClearItems();

		for (int i = 0; i < _Items.Count(); i++)
		{
			CF_TextListboxItem item;
			if (!Class.CastTo(item, _Items.GetConverter(i).GetClass())) break;

			_TextListboxWidget.AddItem(item.Text, item, 0);
			_TextListboxWidget.SetItemColor(i, 0, item.Color);

			if (selectedItem && selectedItem == item)
			{
				selectedRow = i;
			}
		}

		_TextListboxWidget.SelectRow(i);
		NotifyPropertyChanged(Selected, "Selected");
	}
};
