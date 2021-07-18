class CF_CollectionEventArgs : CF_EventArgs
{
	override string ToStr()
	{
		string str = super.ToStr();
		return str;
	}

	void Process(CF_MVVM_View view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		CF_Trace trace(this, "Process", "" + view, "" + model, "" + collection, ToStr());
	}
};