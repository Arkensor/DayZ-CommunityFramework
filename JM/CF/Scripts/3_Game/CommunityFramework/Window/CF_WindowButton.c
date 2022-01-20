class CF_WindowButton : CF_Model
{
	autoptr CF_EventHandler OnClick = new CF_EventHandler();

	private string m_Image;
	private bool m_IsVisible;

	void CF_WindowButton(string image)
	{
		m_Image = image;
		m_IsVisible = true;
	}

	bool IsVisible()
	{
		return m_IsVisible;
	}

	void SetVisible(bool visible)
	{
		m_IsVisible = visible;
		
		NotifyPropertyChanged("m_IsVisible");
	}

	void OnClickButton(CF_ModelBase sender, CF_MouseEventArgs args)
	{
#ifdef CF_WINDOWS_TRACE
		auto trace = CF_Trace_2(this, "Toggle").Add(sender).Add(args);
#endif

		OnClick.Invoke(this, args);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/windows/button.layout";
	}
};
