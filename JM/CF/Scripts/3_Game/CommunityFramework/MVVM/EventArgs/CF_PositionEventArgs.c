class CF_PositionEventArgs : CF_ViewEventArgs
{
	int X;
	int Y;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " X=" + X;
		str += " Y=" + Y;
		return str;
	}
};
