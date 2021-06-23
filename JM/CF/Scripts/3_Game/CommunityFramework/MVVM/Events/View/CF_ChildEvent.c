class CF_ChildEvent : CF_PositionEvent
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
