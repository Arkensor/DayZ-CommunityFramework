class CF_CollectionInsertEventArgs : CF_CollectionEventArgs
{
	int Index;

	void CF_CollectionInsertEventArgs(int index)
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
