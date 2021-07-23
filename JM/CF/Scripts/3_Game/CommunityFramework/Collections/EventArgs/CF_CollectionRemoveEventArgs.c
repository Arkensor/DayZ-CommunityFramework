class CF_CollectionRemoveEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionRemoveEventArgs(int index)
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

		view.OnModel_Children_Remove(collection, this);
	}
};