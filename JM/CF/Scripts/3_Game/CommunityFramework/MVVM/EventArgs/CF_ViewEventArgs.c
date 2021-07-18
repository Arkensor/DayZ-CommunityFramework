class CF_ViewEventArgs : CF_EventArgs
{
	Widget Target;
	bool Continue = true;

	override string ToStr()
	{
		string str = super.ToStr();
		str += " Target=" + Target;
		str += " Continue=" + Continue;
		return str;
	}
};
