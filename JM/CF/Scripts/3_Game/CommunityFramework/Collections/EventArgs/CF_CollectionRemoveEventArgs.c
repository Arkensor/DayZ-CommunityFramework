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
};
