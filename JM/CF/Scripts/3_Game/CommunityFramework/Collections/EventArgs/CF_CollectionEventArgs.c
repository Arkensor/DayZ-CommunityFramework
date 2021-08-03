class CF_CollectionEventArgs : CF_EventArgs
{
	override string ToStr()
	{
		string str = super.ToStr();
		return str;
	}

	void Process(CF_ViewModel view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Process", "" + view, "" + model, "" + collection, ToStr());
		#endif
	}
};