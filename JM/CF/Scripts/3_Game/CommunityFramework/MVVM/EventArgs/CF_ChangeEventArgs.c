class CF_ChangeEventArgs : CF_PositionEventArgs
{
	string What;
	bool Finished;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " What=" + What;
		str += " Finished=" + Finished;
		return str;
	}
};
