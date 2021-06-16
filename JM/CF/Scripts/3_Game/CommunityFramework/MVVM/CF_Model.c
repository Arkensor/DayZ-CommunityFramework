/**
 * @brief
 */
class CF_Model
{
	bool DestroyViewOnDestruction = true;

	void ~CF_Model()
	{
		CF_Trace trace(this, "~CF_Model");

		if (DestroyViewOnDestruction)
		{
			CF.MVVM.Destroy(this);
		}
	}

	void NotifyPropertyChanged(string property)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		
		CF.MVVM.NotifyPropertyChanged(this, property);
	}
};