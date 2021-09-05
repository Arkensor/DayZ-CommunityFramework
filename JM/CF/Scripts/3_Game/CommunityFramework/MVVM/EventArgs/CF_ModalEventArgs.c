class CF_ModalEventArgs : CF_PositionEventArgs
{
	int Code;
	int Result;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Code=" + Code;
		str += " Result=" + Result;
		return str;
	}
};
