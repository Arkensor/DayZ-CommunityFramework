class CF_CollectionRemoveEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionRemoveEventArgs(int index)
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
