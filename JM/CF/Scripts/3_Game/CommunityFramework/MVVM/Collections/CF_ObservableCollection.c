class CF_ObservableCollection : CF_Collection
{
	private CF_ModelBase m_Model;
	private string m_Property;

	void Init(CF_ModelBase model, string prop = "")
	{
		#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
		#endif

		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Init", "" + model, prop);
		#endif

		m_Model = model;
		m_Property = prop;
	}

	void NotifyCollectionChanged(CF_CollectionEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "NotifyCollectionChanged", evt.ToStr());
		#endif

		if (m_Model == null) return;

		CF_MVVM.NotifyPropertyChanged(m_Model, m_Property, evt);
	}
};