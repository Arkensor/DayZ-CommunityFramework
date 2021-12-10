class JMModuleBinding
{
	protected string m_CallbackFunction;

	protected string m_UAInputName;

	protected bool m_CanBeUsedInMenu;
	
	void JMModuleBinding( string callback, string input, bool menu = false ) 
	{	
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "JMModuleBinding").Add(callback).Add(input).Add(menu);
		#endif
	
		m_CallbackFunction = callback;

		m_UAInputName = input;

		m_CanBeUsedInMenu = menu;
	}
	
	bool CanBeUsedInMenu() 
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "CanBeUsedInMenu");
		#endif

		return m_CanBeUsedInMenu;
	}
	
	string GetCallBackFunction() 
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "GetCallBackFunction");
		#endif

		return m_CallbackFunction;
	}

	string GetUAInputName()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "GetUAInputName");
		#endif

		return m_UAInputName;
	}
}