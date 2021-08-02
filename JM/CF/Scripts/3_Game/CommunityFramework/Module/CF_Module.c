class CF_Module : CF_Model
{
	string GetLayoutFile()
	{
		return "";
	}

	void Open(Widget parent = null)
	{
		string layout = GetLayoutFile();
		if (layout == string.Empty) return;

		CF_MVVM.Create(this, layout, parent);
	}

	void Close()
	{
		CF_MVVM.Destroy(this);
	}
};