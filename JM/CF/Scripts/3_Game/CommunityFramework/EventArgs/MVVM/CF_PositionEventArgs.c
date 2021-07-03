class CF_PositionEventArgs : CF_ViewEventArgs
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
