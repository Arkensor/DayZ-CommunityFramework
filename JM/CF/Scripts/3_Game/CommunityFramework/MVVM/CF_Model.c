/**
 * @brief	Simple typedef to keep track of what the base class is for models. 
 * 			Would like to use 'Class' in the future instead of 'Managed'
 */
typedef Managed CF_ModelBase;

/**
 * @brief
 */
class CF_Model : Managed
{
	void ~CF_Model()
	{
		CF_Trace trace(this, "~CF_Model");

		#ifndef SERVER
		CF.MVVM.Destroy(this);
		#endif
	}

	void NotifyPropertyChanged(string property, CF_EventArgs evt = null)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		
		CF.MVVM.NotifyPropertyChanged(this, property, evt);
	}

	string GetLayout()
	{
		return "";
	}
};
