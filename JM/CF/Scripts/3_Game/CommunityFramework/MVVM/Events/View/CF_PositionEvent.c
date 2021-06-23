class CF_PositionEvent : CF_ViewEvent
{
	int X;
	int Y;

	override string String()
	{
		string str = super.String();
		str += " X=" + X;
		str += " Y=" + Y;
		return str;
	}
};
