class CF_EventLoginArgs : CF_EventArgs
{
	string Line1;
	string Line2;

	void CF_EventLoginArgs(string line1, string line2)
	{
		Line1 = line1;
		Line2 = line2;
	}
};
