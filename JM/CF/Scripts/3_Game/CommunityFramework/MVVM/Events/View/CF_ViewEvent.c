class CF_ViewEvent : CF_Event
{
	Widget Target;
	bool Continue = true;

	override string String()
	{
		string str = super.String();
		str += " Target=" + Target;
		str += " Continue=" + Continue;
		return str;
	}
};
