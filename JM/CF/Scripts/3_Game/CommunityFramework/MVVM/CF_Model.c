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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_Model");
		#endif

		#ifndef SERVER
		CF_MVVM.Destroy(this);
		#endif
	}

	void NotifyPropertyChanged(string property, CF_EventArgs evt = null)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "NotifyPropertyChanged", "" + property);
		#endif
		
		CF_MVVM.NotifyPropertyChanged(this, property, evt);
	}

	string GetLayoutFile()
	{
		return "";
	}
};
