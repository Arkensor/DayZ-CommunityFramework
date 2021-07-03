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
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Items, "Items");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextListboxWidget, w);
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
		NotifyPropertyChanged("Selected");
	}
};
