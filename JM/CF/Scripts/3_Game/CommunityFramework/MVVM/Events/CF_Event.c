class CF_Event
{
	Widget Target;
	bool Continue = true;

	string String()
	{
		return "Target=" + Target + " Continue=" + Continue;
	}
};
