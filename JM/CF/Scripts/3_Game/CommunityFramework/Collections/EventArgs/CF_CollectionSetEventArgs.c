class CF_CollectionSetEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionSetEventArgs(int index)
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
