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
		#ifndef SERVER
		CF_MVVM.Destroy(this);
		#endif
	}

	void NotifyPropertyChanged(string property, CF_EventArgs evt = null)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "NotifyPropertyChanged").Add(property);
		#endif
		
		CF_MVVM.NotifyPropertyChanged(this, property, evt);
	}

	string GetLayoutFile()
	{
		return "";
	}
	
	string ToStr()
	{
		return "";
	}

	/**
	 * @note When overriding and adding to the instance, you must return true.
	 */
	bool CF_OnDebugUpdate(CF_Debug instance, CF_DebugUI_Type type)
	{
		return false;
	}
};
