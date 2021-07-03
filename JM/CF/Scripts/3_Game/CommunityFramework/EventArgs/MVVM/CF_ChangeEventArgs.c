class CF_ChangeEventArgs : CF_PositionEventArgs
{
	bool Finished;

	override string String()
	{
		string str = super.String();
		str += " Finished=" + Finished;
		return str;
	}
};
