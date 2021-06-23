class CF_ObservableCollection : CF_Collection
{
	private CF_Model_Base m_Model;
	private string m_Property;

	void Init(CF_Model_Base model, string prop)
	{
		CF_Trace Trace(this, "Init", "" + model, prop);

		m_Model = model;
		m_Property = prop;
	}

	void NotifyCollectionChanged(CF_CollectionEvent evt)
	{
		CF_Trace trace(this, "NotifyCollectionChanged", evt.String());

		CF.MVVM.NotifyPropertyChanged(m_Model, m_Property, evt);
	}
};