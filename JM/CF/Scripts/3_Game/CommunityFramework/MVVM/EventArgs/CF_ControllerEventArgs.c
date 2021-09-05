class CF_ControllerEventArgs : CF_ViewEventArgs
{
	int Control;
	int Value;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Control=" + Control;
		str += " Value=" + Value;
		return str;
	}
};
