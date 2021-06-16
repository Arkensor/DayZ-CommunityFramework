class CF_ControllerEvent : CF_Event
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
