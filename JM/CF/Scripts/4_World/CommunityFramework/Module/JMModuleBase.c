class JMModuleBase : CF_Module
{
	protected bool m_Enabled;
	protected bool m_PreventInput;
	protected ref set< ref JMModuleBinding > m_Bindings;
	
	void JMModuleBase()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "JMModuleBase");
		#endif

		m_Enabled = true;
		m_PreventInput = false;
		m_Bindings = new set< ref JMModuleBinding >;
	}
	
	void ~JMModuleBase()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~JMModuleBase");
		#endif

	}
	
	void Init()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Init");
		#endif

		RegisterKeyMouseBindings();
	}

	void Toggle()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Toggle");
		#endif

		m_Enabled = !m_Enabled;
	}

	void PreventInput(bool prevent)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "PreventInput").Add(prevent);
		#endif

		m_PreventInput = prevent;
	}

	string GetModuleName()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetModuleName");
		#endif

		return ClassName();
	}

	typename GetModuleType()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetModuleType");
		#endif

		return GetModuleName().ToType();
	}

	bool IsEnabled()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "IsEnabled");
		#endif

		return m_Enabled;
	}

	bool IsPreventingInput()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "IsPreventingInput");
		#endif

		return m_PreventInput;
	}

	/**
	 * Can't change dynamically, only used on module init, if false 
	 * and is mission host, the module is destroyed and forgotten.
	 */
	bool IsServer()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "IsServer");
		#endif

		return true;
	}

	/**
	 * Can't change dynamically, only used on module init, if false 
	 * and is mission client, the module is destroyed and forgotten.
	 */
	bool IsClient()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "IsClient");
		#endif

		return true;
	}

	void RegisterKeyMouseBindings() 
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "RegisterKeyMouseBindings");
		#endif

	}
	
	/**
	 * Deprecated, use RegisterBinding instead.
	 */
	void RegisterKeyMouseBinding( JMModuleBinding binding ) 
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "RegisterKeyMouseBinding").Add(binding);
		#endif

		RegisterBinding( binding );
		Error( GetModuleName() + "::RegisterKeyMouseBinding has been deprecated, use " + GetModuleName() + "::RegisterBinding instead." );
	}

	void RegisterBinding( JMModuleBinding binding ) 
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "RegisterBinding").Add(binding);
		#endif

		m_Bindings.Insert( binding );
	}
	
	set< ref JMModuleBinding > GetBindings()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetBindings");
		#endif

		return m_Bindings;
	}

	// Events 

	/**
	 * Is called every mission frame
	 * 
	 * @timeslice time of previous update
	 */
	void OnUpdate( float timeslice ) 
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnUpdate").Add(timeslice);
		#endif

	}

	void OnSettingsUpdated()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnSettingsUpdated");
		#endif

	}

	void OnClientPermissionsUpdated()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnClientPermissionsUpdated");
		#endif

	}

	void OnInit()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnInit");
		#endif

	}
	
	void OnMissionStart()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMissionStart");
		#endif

	}
	
	void OnMissionFinish()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMissionFinish");
		#endif

	}
	
	void OnMissionLoaded()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMissionLoaded");
		#endif

	}

	void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this, "OnRPC").Add(sender).Add(target).Add(rpc_type).Add(ctx);
		#endif

	}

	int GetRPCMin()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetRPCMin");
		#endif

		return -1;
	}

	int GetRPCMax()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetRPCMax");
		#endif

		return -1;
	}

	/**
	 * @brief See: WorldCleaupEventTypeID
	 */
	void OnWorldCleanup()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnWorldCleanup");
		#endif

	}

	/**
	 * @brief See: MPSessionStartEventTypeID
	 */
	void OnMPSessionStart()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionStart");
		#endif

	}

	/**
	 * @brief See: MPSessionPlayerReadyEventTypeID
	 */
	void OnMPSessionPlayerReady()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionPlayerReady");
		#endif

	}

	/**
	 * @brief See: MPSessionFailEventTypeID
	 */
	void OnMPSessionFail()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionFail");
		#endif

	}

	/**
	 * @brief See: MPSessionEndEventTypeID
	 */
	void OnMPSessionEnd()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionEnd");
		#endif

	}

	/**
	 * @brief See: ConnectingAbortEventTypeID
	 */
	void OnMPConnectAbort()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPConnectAbort");
		#endif

	}

	/**
	 * @brief See: MPConnectionLostEventTypeID
	 */
	void OnMPConnectionLost( int duration )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnMPConnectionLost").Add(duration);
		#endif

	}

	/**
	 * @brief See: RespawnEventTypeID
	 */
	void OnRespawn( int time )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnRespawn").Add(time);
		#endif

	}

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnClientLogoutCancelled").Add(player).Add(identity);
		#endif

	}

	/**
	 * @brief See: MissionServer::InvokeOnConnect
	 */
	void OnInvokeConnect( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnInvokeConnect").Add(player).Add(identity);
		#endif

	}

	/**
	 * @brief See: MissionServer::InvokeOnDisconnect
	 */
	void OnInvokeDisconnect( PlayerBase player )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnInvokeDisconnect").Add(player);
		#endif

	}

	/**
	 * @brief See: ClientNewEventTypeID
	 */
	void OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this, "OnClientNew").Add(player).Add(identity).Add(pos).Add(ctx);
		#endif

	}

	/**
	 * @brief See: ClientRespawnEventTypeID
	 */
	void OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientRespawn").Add(player).Add(identity);
		#endif

	}

	/**
	 * @brief See: ClientReadyEventTypeID
	 */
	void OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnClientReady").Add(player).Add(identity);
		#endif

	}

	/**
	 * @brief See: ClientPrepareEventTypeID
	 */
	void OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientPrepare").Add(identity).Add(useDB).Add(pos).Add(yaw).Add(preloadTimeout);
		#endif

	}

	/**
	 * @brief See: ClientReconnectEventTypeID
	 */
	void OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientReconnect").Add(player).Add(identity);
		#endif

	}

	/**
	 * @brief See: ClientDisconnectedEventTypeID
	 */
	void OnClientLogout( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientLogout").Add(player).Add(identity).Add(logoutTime).Add(authFailed);
		#endif

	}

	/**
	 * @brief See: MissionServer::PlayerDisconnected - Fires when the player has disconnected from the server (OnClientReconnect won't fire)
	 */
	void OnClientDisconnect( PlayerBase player, PlayerIdentity identity, string uid )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientDisconnect").Add(player).Add(identity).Add(uid);
		#endif

	}

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled( PlayerBase player )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnClientLogoutCancelled").Add(player);
		#endif

	}
}
