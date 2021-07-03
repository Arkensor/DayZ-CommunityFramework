class CF_CollectionClearEventArgs : CF_CollectionEventArgs
{
	void CF_CollectionClearEventArgs()
	{
	}

	override string String()
	{
		string str = super.String();
		return str;
	}

	override void Process(CF_MVVM_View view, CF_ModelBase model, CF_ObservableCollection collection)
	{
		CF_Trace trace(this, "Process", "" + model, "" + collection, String());

		view.OnModel_Children_Clear(collection, this);
	}
};