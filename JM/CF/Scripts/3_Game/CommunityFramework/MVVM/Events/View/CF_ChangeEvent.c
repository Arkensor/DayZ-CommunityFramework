class CF_ChangeEvent : CF_PositionEvent
{
	bool Finished;

	override string String()
	{
		string str = super.String();
		str += " Finished=" + Finished;
		return str;
	}
};
