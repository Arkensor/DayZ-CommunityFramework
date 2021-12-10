class CF_WindowButtonArgs : CF_EventArgs
{
	CF_WindowButton Button;
	bool State;
};

class CF_WindowButton : CF_Model
{
	autoptr CF_EventHandler OnClick = new CF_EventHandler();

	private string m_Image;
	private bool m_Toggled;

	private string m_OnImage;
	private string m_OffImage;

	void CF_WindowButton(string onImage, string offImage)
	{
		m_OnImage = onImage;
		m_OffImage = offImage;
	}

	void Toggle(CF_ModelBase sender, CF_MouseEventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Toggle").Add(sender).Add(args);
#endif

		m_Toggled = !m_Toggled;

		if (m_Toggled)
		{
			m_Image = m_OffImage;
		}
		else
		{
			m_Image = m_OnImage;
		}

		CF_WindowButtonArgs eventArgs = new CF_WindowButtonArgs();
		eventArgs.Button = this;
		eventArgs.State = m_Toggled;
		OnClick.Invoke(this, eventArgs);

		NotifyPropertyChanged("m_Image");
	}
};
