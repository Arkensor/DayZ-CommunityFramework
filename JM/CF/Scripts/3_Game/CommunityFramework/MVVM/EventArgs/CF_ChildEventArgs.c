class CF_ChildEventArgs : CF_PositionEventArgs
{
	Widget Child;
	bool Remove;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Child=" + Child;
		str += " Remove=" + Remove;
		return str;
	}
};
