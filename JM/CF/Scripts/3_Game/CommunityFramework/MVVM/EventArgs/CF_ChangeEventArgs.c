class CF_ChangeEventArgs : CF_PositionEventArgs
{
	string What;
	bool Finished;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " What=" + What;
		str += " Finished=" + Finished;
		return str;
	}
};
