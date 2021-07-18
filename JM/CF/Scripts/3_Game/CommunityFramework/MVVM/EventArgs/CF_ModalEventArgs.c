class CF_ModalEventArgs : CF_PositionEventArgs
{
	int Code;
	int Result;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Code=" + Code;
		str += " Result=" + Result;
		return str;
	}
};
