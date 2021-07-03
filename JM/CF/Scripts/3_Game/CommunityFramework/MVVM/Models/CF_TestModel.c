
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
		CF.Windows.Handle(m_WindowHandle);

		CF_Window window;
		CF.Windows.Retrieve(m_WindowHandle, window);

		window.SetModel(this);
	}

	void CloseWindow()
	{
		CF.Windows.Destroy(m_WindowHandle);
	}

	void OnChange(CF_ChangeEventArgs evt)
	{
		CF_Trace trace(this, "OnChange", evt.String());
		
		evt.Continue = BlockInput;

		ButtonText = TextInput;
		NotifyPropertyChanged("ButtonText");
	}

	void OnClick(CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "OnClick", evt.String());

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

	void Remove(CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "Remove", evt.String());

		int index = m_Parent.Test.Find(this);
		m_Parent.Test.Remove(index);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/mvvm/testitem.layout";
	}
};