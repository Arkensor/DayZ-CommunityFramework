class CF_CollectionSetEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionSetEventArgs(int index)
	{
		Index = index;
	}

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Index=" + Index;
		return str;
	}
};
