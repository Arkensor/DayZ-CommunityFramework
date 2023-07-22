class CF_CollectionInsertAtEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertAtEventArgs(int index)
	{
		Index = index;
	}

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Index=" + Index;
		return str;
	}
};
