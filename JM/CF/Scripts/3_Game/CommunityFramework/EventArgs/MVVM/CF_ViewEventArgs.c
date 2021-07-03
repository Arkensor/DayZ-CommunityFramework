class CF_ViewEventArgs : CF_EventArgs
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
