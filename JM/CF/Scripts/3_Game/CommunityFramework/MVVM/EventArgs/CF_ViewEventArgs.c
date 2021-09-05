class CF_ViewEventArgs : CF_EventArgs
{
	Widget Target;
	bool Continue = true;

	override string GetDebugName()
	{
		string str = super.GetDebugName();
		str += " Target=" + Target;
		str += " Continue=" + Continue;
		return str;
	}
};
