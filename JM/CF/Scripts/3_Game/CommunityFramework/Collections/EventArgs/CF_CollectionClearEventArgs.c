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
		CF_Trace trace(this, "Process", "" + model, "" + collection, ToStr());

		view.OnModel_Children_Clear(collection, this);
	}
};