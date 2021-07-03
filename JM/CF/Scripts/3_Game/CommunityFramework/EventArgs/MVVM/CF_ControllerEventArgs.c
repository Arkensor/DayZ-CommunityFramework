class CF_ControllerEventArgs : CF_ViewEventArgs
{
	int Control;
	int Value;

	override string String()
	{
		string str = super.String();
		str += " Control=" + Control;
		str += " Value=" + Value;
		return str;
	}
};
