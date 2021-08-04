
/**
 * @brief Inheriting from 'CF_Model' is not a requirement, must re-implement the 'GetLayoutFile' method.
 */
class CF_TestModel : CF_Model
{
	int Index;

	string TextInput = "Input?";
	bool BlockInput = false;

	string ButtonText = "Press??";

	ref CF_ObservableArray<CF_TestItemModel> Test = new CF_ObservableArray<CF_TestItemModel>();
	
	void CF_TestModel()
	{
	}

	void OpenWindow()
	{
	}

	void CloseWindow()
	{
	}

	void OnCheckboxChange(CF_ModelBase sender, CF_ChangeEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCheckboxChange", evt.ToStr());
		#endif

		evt.Continue = true;

		Print(BlockInput);
		//NotifyPropertyChanged("BlockInput");
	}

	void OnChange(CF_ModelBase sender, CF_ChangeEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", evt.ToStr());
		#endif
		
		evt.Continue = BlockInput;

		ButtonText = TextInput;
		NotifyPropertyChanged("ButtonText");
	}

	void OnClick(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnClick", evt.ToStr());
		#endif

		Index++;

		ButtonText = "Pressed " + Index + " times!";
		NotifyPropertyChanged("ButtonText");

		CF_TestItemModel item = new CF_TestItemModel(this, Index);
		Test.Insert(item);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/mvvm/test.layout";
	}
};

class CF_TestItemModel : CF_Model
{
	string ButtonText = "NOT SET!";

	private CF_TestModel m_Parent;

	void CF_TestItemModel(CF_TestModel parent, int index)
	{
		m_Parent = parent;

		ButtonText = "Press To Remove (" + index + ")";
	}

	void Remove(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Remove", evt.ToStr());
		#endif

		int index = m_Parent.Test.Find(this);
		m_Parent.Test.Remove(index);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/mvvm/testitem.layout";
	}
};