class CF_DebugUI_Type
{
	private ref map<string, bool> m_Types = new map<string, bool>();

	void CF_DebugUI_Type()
	{
		OnRegisterTypes();
	}

	void Register(string type, bool enabled = false)
	{
		Set(type, enabled);
	}

	void Set(string type, bool enabled)
	{
		if (m_Types.Contains(type))
		{
			m_Types[type] = enabled;
			return;
		}

		m_Types.Insert(type, enabled);
	}

	bool Get(string type)
	{
		if (!m_Types.Contains(type)) return false;
		
		return m_Types[type];
	}

	void OnRegisterTypes()
	{

	}
};
