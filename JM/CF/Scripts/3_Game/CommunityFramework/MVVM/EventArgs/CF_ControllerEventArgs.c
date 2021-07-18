class CF_ControllerEventArgs : CF_ViewEventArgs
{
	int Control;
	int Value;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Control=" + Control;
		str += " Value=" + Value;
		return str;
	}
};
