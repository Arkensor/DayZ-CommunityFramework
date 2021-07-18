class CF_PositionEventArgs : CF_ViewEventArgs
{
	int X;
	int Y;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " X=" + X;
		str += " Y=" + Y;
		return str;
	}
};
