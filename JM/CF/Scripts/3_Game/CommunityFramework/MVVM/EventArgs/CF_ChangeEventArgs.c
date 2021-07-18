class CF_ChangeEventArgs : CF_PositionEventArgs
{
	bool Finished;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Finished=" + Finished;
		return str;
	}
};
