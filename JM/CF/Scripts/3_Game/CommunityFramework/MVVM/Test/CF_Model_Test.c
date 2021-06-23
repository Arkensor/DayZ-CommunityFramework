/**
 * @brief Inheriting from 'CF_Model' is not a requirement, must re-implement the 'GetLayout' method.
 */
class CF_Model_Test : CF_Model
{
	int Index;

	string ButtonText = "Press??";

	ref CF_ObservableArray<CF_Model_Test2> Test = new CF_ObservableArray<CF_Model_Test2>();

	void OnClick(CF_MouseEvent evt)
	{
		CF_Trace trace(this, "OnClick", evt.String());

		Index++;

		ButtonText = "Pressed " + Index + " times!";
		NotifyPropertyChanged("ButtonText");


		CF_Model_Test2 item = new CF_Model_Test2(this, Index);
		Test.Insert(item);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/samples/mvvm.layout";
	}
};

class CF_Model_Test2 : CF_Model
{
	string ButtonText = "NOT SET!";

	private CF_Model_Test m_Parent;

	void CF_Model_Test2(CF_Model_Test parent, int index)
	{
		m_Parent = parent;

		ButtonText = "Press To Remove (" + index + ")";
	}

	void Remove(CF_MouseEvent evt)
	{
		CF_Trace trace(this, "Remove", evt.String());

		int index = m_Parent.Test.Find(this);
		m_Parent.Test.Remove(index);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/samples/mvvm2.layout";
	}
};