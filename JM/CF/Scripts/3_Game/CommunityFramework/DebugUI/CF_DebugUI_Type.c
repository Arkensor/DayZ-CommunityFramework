class CF_DebugUI_Type
{
	private ref map<string, bool> m_Types = new map<string, bool>();

	void CF_DebugUI_Type()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_DebugUI_Type");
		#endif

		OnRegisterTypes();
	}

	void Register(string type, bool enabled = false)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Get", "" + type, "" + enabled);
		#endif

		Set(type, enabled);
	}

	void Set(string type, bool enabled)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Get", "" + type, "" + enabled);
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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Get", "" + type);
		#endif

		if (!m_Types.Contains(type)) return false;
		
		return m_Types[type];
	}

	void OnRegisterTypes()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnRegisterTypes");
		#endif


	}
};
