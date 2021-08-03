class CF_CollectionClearEventArgs : CF_CollectionEventArgs
{
	void CF_CollectionClearEventArgs()
	{
	}

	override string ToStr()
	{
		string str = super.ToStr();
		return str;
	}

	override void Process(CF_ViewModel view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Process", "" + model, "" + collection, ToStr());
		#endif

		view.OnModel_Children_Clear(collection, this);
	}
};