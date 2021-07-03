class CF_ObservableCollection : CF_Collection
{
	private CF_ModelBase m_Model;
	private string m_Property;

	void Init(CF_ModelBase model, string prop)
	{
		#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
		#endif

		CF_Trace trace(this, "Init", "" + model, prop);

		m_Model = model;
		m_Property = prop;
	}

	void NotifyCollectionChanged(CF_CollectionEventArgs evt)
	{
		CF_Trace trace(this, "NotifyCollectionChanged", evt.String());

		CF.MVVM.NotifyPropertyChanged(m_Model, m_Property, evt);
	}
};