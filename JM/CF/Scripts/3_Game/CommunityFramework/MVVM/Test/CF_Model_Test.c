/**
 * @brief
 */
class CF_Model_Test : CF_Model
{
	int Index;

	string ButtonText = "Press??";

	ref CF_Array<CF_Model_Test2> Test = new CF_Array<CF_Model_Test2>("JM/CF/GUI/layouts/samples/mvvm2.layout");

	void OnClick(CF_MouseEvent evt)
	{
		CF_Trace trace(this, "OnClick", evt.String());

		Index++;

		ButtonText = "Pressed: " + Index;
		NotifyPropertyChanged("ButtonText");


		CF_Model_Test2 item = new CF_Model_Test2();
		item.ButtonText = "Remove: " + Index;
		item.NotifyPropertyChanged("ButtonText");
		Test.Insert(item);

		NotifyPropertyChanged("Test");
	}
};

class CF_Model_Test2 : CF_Model
{
	string ButtonText = "Press??";

	void Remove(CF_MouseEvent evt)
	{
		delete this;
	}
};