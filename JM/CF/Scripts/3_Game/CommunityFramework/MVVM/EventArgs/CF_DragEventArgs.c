class CF_DragEventArgs : CF_PositionEventArgs
{
	Widget Reciever;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Reciever=" + Reciever;
		return str;
	}
};
