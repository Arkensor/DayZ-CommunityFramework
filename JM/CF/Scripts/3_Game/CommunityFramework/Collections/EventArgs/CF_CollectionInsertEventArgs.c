class CF_CollectionInsertEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertEventArgs(int index)
	{
		Index = index;
	}

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Index=" + Index;
		return str;
	}

	override void Process(CF_ViewModel view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Process", "" + model, "" + collection, ToStr());
		#endif

		view.OnModel_Children_Insert(collection, this);
	}
};