class CF_ModalEvent : CF_PositionEvent
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
