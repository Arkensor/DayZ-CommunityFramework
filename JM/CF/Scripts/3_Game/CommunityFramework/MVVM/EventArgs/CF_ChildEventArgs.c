class CF_ChildEventArgs : CF_PositionEventArgs
{
	Widget Child;
	bool Remove;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Child=" + Child;
		str += " Remove=" + Remove;
		return str;
	}
};
