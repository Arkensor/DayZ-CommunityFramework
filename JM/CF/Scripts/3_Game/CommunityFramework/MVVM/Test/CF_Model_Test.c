/**
 * @brief
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

		ButtonText = "Pressed: " + Index;
		NotifyPropertyChanged("ButtonText");


		CF_Model_Test2 item = new CF_Model_Test2();
		item.ButtonText = "Remove: " + Index;
		Test.Insert(item);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/samples/mvvm.layout";
	}
};

class CF_Model_Test2 : CF_Model
{
	string ButtonText = "Press??";

	void Remove(CF_MouseEvent evt)
	{
		delete this;
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/samples/mvvm2.layout";
	}
};