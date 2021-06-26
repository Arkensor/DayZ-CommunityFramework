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

		CF.MVVM.Destroy(this);
	}

	void NotifyPropertyChanged(string property, CF_Event evt = null)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		
		CF.MVVM.NotifyPropertyChanged(this, property, evt);
	}

	string GetLayout()
	{
		return "LAYOUT NOT SET";
	}
};
