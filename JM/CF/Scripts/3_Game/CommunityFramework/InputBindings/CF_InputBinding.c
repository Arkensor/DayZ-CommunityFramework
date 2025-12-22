class CF_InputBinding
{
	static int PRESS = 1;
	static int RELEASE = 2;
	static int HOLD = 4;
	static int CLICK = 8;
	static int DOUBLE_CLICK = 16;

	ref CF_InputBinding m_Next;

	string m_Function;
	int m_InputID;
	int m_InputLimits;
	bool m_LimitMenu;

	void UpdateLimits()
	{
		UAInput input = GetUApi().GetInputByID(m_InputID);
		m_InputLimits = 0;
		m_InputLimits &= input.IsPressLimit() << 1;
		m_InputLimits &= input.IsReleaseLimit() << 2;
		m_InputLimits &= input.IsHoldLimit() << 3;
		m_InputLimits &= input.IsClickLimit() << 4;
		m_InputLimits &= input.IsDoubleClickLimit() << 5;
	}
};
