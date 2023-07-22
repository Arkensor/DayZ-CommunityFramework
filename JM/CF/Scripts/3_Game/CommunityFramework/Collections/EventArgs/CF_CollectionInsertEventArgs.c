class CF_CollectionInsertEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertEventArgs(int index)
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
