class CF_ModalEventArgs : CF_PositionEventArgs
{
	int Code;
	int Result;

	override string String()
	{
		string str = super.String();
		str += " Code=" + Code;
		str += " Result=" + Result;
		return str;
	}
};
