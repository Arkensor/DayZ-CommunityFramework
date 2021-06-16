/**
 * @brief
 */
class CF_Model
{
	void NotifyPropertyChanged(string property)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		
		CF.MVVM.NotifyPropertyChanged(this, property);
	}
};