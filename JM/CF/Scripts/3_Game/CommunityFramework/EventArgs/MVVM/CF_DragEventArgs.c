class CF_DragEventArgs : CF_PositionEventArgs
{
	Widget Reciever;

	override string String()
	{
		string str = super.String();
		str += " Reciever=" + Reciever;
		return str;
	}
};
