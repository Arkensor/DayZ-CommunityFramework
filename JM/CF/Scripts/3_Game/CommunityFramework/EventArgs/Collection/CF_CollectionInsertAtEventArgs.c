class CF_CollectionInsertAtEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertAtEventArgs(int index)
	{
		Index = index;
	}

	override string String()
	{
		string str = super.String();
		str += " Index=" + Index;
		return str;
	}

	override void Process(CF_MVVM_View view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		CF_Trace trace(this, "Process", "" + model, "" + collection, String());

		view.OnModel_Children_InsertAt(collection, this);
	}
};