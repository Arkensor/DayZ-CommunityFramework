class CF_DebugUI_Type
{
	private ref map<string, bool> m_Types = new map<string, bool>();

	void CF_DebugUI_Type()
	{
#ifdef CF_DEBUG_TRACE
		auto trace = CF_Trace_0(this, "CF_DebugUI_Type");
#endif

		OnRegisterTypes();
	}

	void Register(string type, bool enabled = false)
	{
#ifdef CF_DEBUG_TRACE
		auto trace = CF_Trace_1(this, "Get").Add(type).Add(enabled);
#endif

		Set(type, enabled);
	}

	void Set(string type, bool enabled)
	{
#ifdef CF_DEBUG_TRACE
		auto trace = CF_Trace_1(this, "Get").Add(type).Add(enabled);
#endif

		if (m_Types.Contains(type))
		{
			m_Types[type] = enabled;
			return;
		}

		m_Types.Insert(type, enabled);
	}

	bool Get(string type)
	{
#ifdef CF_DEBUG_TRACE
		auto trace = CF_Trace_1(this, "Get").Add(type);
#endif

		if (!m_Types.Contains(type))
			return false;

		return m_Types[type];
	}

	void OnRegisterTypes()
	{
#ifdef CF_DEBUG_TRACE
		auto trace = CF_Trace_0(this, "OnRegisterTypes");
#endif
	}
};