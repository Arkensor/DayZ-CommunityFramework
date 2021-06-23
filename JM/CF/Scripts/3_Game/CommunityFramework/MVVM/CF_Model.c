/**
 * @brief	Simple typedef to keep track of what the base class is for models. 
 * 			Would like to use 'Class' in the future instead of 'Managed'
 */
typedef Managed CF_Model_Base;

/**
 * @brief
 */
class CF_Model : Managed
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

	void NotifyPropertyChanged(string property, CF_Event evt = null)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		
		CF.MVVM.NotifyPropertyChanged(this, property, evt);
	}
};
