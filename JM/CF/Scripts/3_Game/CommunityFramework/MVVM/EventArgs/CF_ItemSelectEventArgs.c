class CF_ItemSelectEventArgs : CF_PositionEventArgs
{
	int Row;
	int Column;

	int OldRow;
	int OldColumn;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Row=" + Row;
		str += " Column=" + Column;
		str += " OldRow=" + OldRow;
		str += " OldColumn=" + OldColumn;
		return str;
	}
};
