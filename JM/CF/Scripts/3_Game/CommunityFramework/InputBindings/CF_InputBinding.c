class CF_InputBinding
{
	static int PRESS = 1;
	static int RELEASE = 2;
	static int HOLD = 4;
	static int CLICK = 8;
	static int DOUBLE_CLICK = 16;

	ref CF_InputBinding m_Next;

	string m_Function;
	UAInput m_Input;
	int m_InputLimits;
	bool m_LimitMenu;

	void UpdateLimits()
	{
		m_InputLimits = 0;
		m_InputLimits &= m_Input.IsPressLimit() << 1;
		m_InputLimits &= m_Input.IsReleaseLimit() << 2;
		m_InputLimits &= m_Input.IsHoldLimit() << 3;
		m_InputLimits &= m_Input.IsClickLimit() << 4;
		m_InputLimits &= m_Input.IsDoubleClickLimit() << 5;
	}
};
