
#ifndef COMPONENT_SYSTEM
static ref CF_TestModel CF_TestModelInstance = new CF_TestModel();
#endif

/**
 * @brief Inheriting from 'CF_Model' is not a requirement, must re-implement the 'GetLayout' method.
 */
class CF_TestModel : CF_Model
{
	int Index;

	string TextInput = "Input?";
	bool BlockInput = false;

	string ButtonText = "Press??";

	ref CF_ObservableArray<CF_TestItemModel> Test = new CF_ObservableArray<CF_TestItemModel>();

	private CF_WindowHandle m_WindowHandle;
	
	void CF_TestModel()
	{
	}

	void OpenWindow()
	{
		CF_Windows.Handle(m_WindowHandle);

		CF_Window window;
		CF_Windows.Retrieve(m_WindowHandle, window);

		window.SetModel(this);
	}

	void CloseWindow()
	{
		CF_Windows.Destroy(m_WindowHandle);
	}

	void OnCheckboxChange(Class sender, CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnCheckboxChange", evt.ToStr());

		evt.Continue = true;

		Print(BlockInput);
	}

	void OnChange(Class sender, CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.ToStr());
		
		evt.Continue = BlockInput;

		ButtonText = TextInput;
		NotifyPropertyChanged("ButtonText");
	}

	void OnClick(Class sender, CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "OnClick", evt.ToStr());

		Index++;

		ButtonText = "Pressed " + Index + " times!";
		NotifyPropertyChanged("ButtonText");

		CF_TestItemModel item = new CF_TestItemModel(this, Index);
		Test.Insert(item);
	}

	override string GetLayout()
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

	void Remove(Class sender, CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "Remove", evt.ToStr());

		int index = m_Parent.Test.Find(this);
		m_Parent.Test.Remove(index);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/mvvm/testitem.layout";
	}
};