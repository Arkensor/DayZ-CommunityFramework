class CF_CollectionSwapEventArgs : CF_CollectionEventArgs
{
	int IndexA;
	int IndexB;

	void CF_CollectionSwapEventArgs(int indexa, int indexb)
	{
		IndexA = indexa;
		IndexB = indexb;

		if (IndexA > IndexB)
		{
			int temp = IndexA;
			IndexA = IndexB;
			IndexB = temp;
		}
	}

	override string ToStr()
	{
		string str = super.ToStr();
		str += " IndexA=" + IndexA;
		str += " IndexB=" + IndexB;
		return str;
	}
};
