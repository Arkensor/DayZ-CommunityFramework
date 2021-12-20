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

		SetOn(false, false);
	}

	void SetOn(bool value, bool sendEvent = true)
	{
#ifdef CF_WINDOWS_TRACE
		auto trace = CF_Trace_1(this, "Toggle").Add(value);
#endif

		m_Toggled = value;

		if (m_Toggled)
		{
			m_Image = m_OffImage;
		}
		else
		{
			m_Image = m_OnImage;
		}

		if (sendEvent)
		{
			CF_WindowButtonArgs eventArgs = new CF_WindowButtonArgs();
			eventArgs.Button = this;
			eventArgs.State = m_Toggled;
			OnClick.Invoke(this, eventArgs);
		}

		NotifyPropertyChanged("m_Image");
	}

	bool IsToggled()
	{
		return m_Toggled;
	}

	void Toggle(CF_ModelBase sender, CF_MouseEventArgs args)
	{
#ifdef CF_WINDOWS_TRACE
		auto trace = CF_Trace_2(this, "Toggle").Add(sender).Add(args);
#endif

		SetOn(m_Toggled);
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/windows/button.layout";
	}
};
