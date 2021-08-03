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
};
