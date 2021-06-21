class CF_TextListboxItem
{
	string Text;
	Class Data;
	int Color;
};

class CF_TextListboxWidget : CF_BaseListboxWidget
{
	reference string Items;

	protected TextListboxWidget _TextListboxWidget;
	protected ref array<ref CF_TextListboxItem> _Items = new array<ref CF_TextListboxItem>();

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_TextListboxWidget, w);
	}

	void OnView_Items(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, Items, 0, _Items);
	}

	void OnModel_Items(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, Items, 0, _Items);

		for (int i = 0; i < _Items.Count(); i++)
		{
			_TextListboxWidget.AddItem(_Items[i].Text, _Items[i].Data, 0);
			_TextListboxWidget.SetItemColor(i, 0, _Items[i].Color);
		}
	}
};
