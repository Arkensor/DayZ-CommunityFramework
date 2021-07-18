class CF_DragEventArgs : CF_PositionEventArgs
{
	Widget Reciever;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Reciever=" + Reciever;
		return str;
	}
};
