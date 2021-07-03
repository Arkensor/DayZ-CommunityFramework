class CF_ChildEventArgs : CF_PositionEventArgs
{
	Widget Child;
	bool Remove;

	override string String()
	{
		string str = super.String();
		str += " Child=" + Child;
		str += " Remove=" + Remove;
		return str;
	}
};
