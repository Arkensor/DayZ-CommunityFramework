/**
 * @brief
 */
class CF_Model_Test : CF_Model
{
	int Index;

	string ButtonText = "Press??";

	void OnClick(CF_MouseEvent evt)
	{
		CF_Trace trace(this, "OnClick", evt.String());

		ButtonText = "Pressed: " + Index++;
		NotifyPropertyChanged("ButtonText");
	}
};