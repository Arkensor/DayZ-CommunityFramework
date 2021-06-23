class CF_DragEvent : CF_PositionEvent
{
	Widget Reciever;

	override string String()
	{
		string str = super.String();
		str += " Reciever=" + Reciever;
		return str;
	}
};
