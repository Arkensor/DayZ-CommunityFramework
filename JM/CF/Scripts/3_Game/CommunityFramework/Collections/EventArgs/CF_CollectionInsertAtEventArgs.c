class CF_CollectionInsertAtEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertAtEventArgs(int index)
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
		CF_Trace trace(this, "Process", "" + model, "" + collection, ToStr());

		view.OnModel_Children_InsertAt(collection, this);
	}
};