class CF_KeyEventArgs : CF_PositionEventArgs
{
	int Key;
	CF_KeyState State;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Key=" + Key;
		str += " State=" + State;
		return str;
	}
};
