class JMModuleBase
{
	protected bool m_Enabled;
	protected bool m_PreventInput;
	protected ref set< ref JMModuleBinding > m_Bindings;
	
	void JMModuleBase()
	{
		m_Enabled = true;
		m_PreventInput = false;
		m_Bindings = new set< ref JMModuleBinding >;
	}
	
	void ~JMModuleBase()
	{
	}
	
	void Init()
	{
		RegisterKeyMouseBindings();
	}

	void Toggle()
	{
		m_Enabled = !m_Enabled;
	}

	void PreventInput(bool prevent)
	{
		m_PreventInput = prevent;
	}

	string GetModuleName()
	{
		return ClassName();
	}

	typename GetModuleType()
	{
		return GetModuleName().ToType();
	}

	bool IsEnabled()
	{
		return m_Enabled;
	}

	bool IsPreventingInput()
	{
		return m_PreventInput;
	}

	void RegisterKeyMouseBindings() 
	{
	}
	
	/**
	 * Deprecated, use RegisterBinding instead.
	 */
	void RegisterKeyMouseBinding( JMModuleBinding binding ) 
	{
		RegisterBinding( binding );
		Error( GetModuleName() + "::RegisterKeyMouseBinding has been deprecated, use " + GetModuleName() + "::RegisterBinding instead." );
	}

	void RegisterBinding( JMModuleBinding binding ) 
	{
		m_Bindings.Insert( binding );
	}
	
	set< ref JMModuleBinding > GetBindings()
	{
		return m_Bindings;
	}

	// Override functions 
	
	void OnUpdate( float timeslice ) 
	{
	}

	void ReloadSettings()
	{
	}

	void OnClientPermissionsUpdated()
	{
	}
	
	/* Mission Functions */
	
	void OnMissionStart()
	{
	}
	
	void OnMissionFinish()
	{
	}
	
	void OnMissionLoaded()
	{
	}

	bool OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
		return false;
	}

	bool OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		return false;
	}

	bool OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
		return false;
	}

	bool OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
		return false;
	}

	bool OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		return false;
	}

	bool OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
		return false;
	}

	bool OnClientDisconnected( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
		return false;
	}
}
