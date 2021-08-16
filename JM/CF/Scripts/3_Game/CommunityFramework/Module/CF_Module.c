class CF_Module : CF_TimerBase
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	int m_CF_RPC_Minimum;
	int m_CF_RPC_Maximum;

	void Bind(string function, string input)
	{
		m_CF_Bindings.Bind(function, input);

		EnableUpdate();
	}

	void Bind(string function, UAInput input)
	{
		m_CF_Bindings.Bind(function, input);

		EnableUpdate();
	}

	void Bind(CF_InputBinding binding)
	{
		m_CF_Bindings.Bind(binding);

		EnableUpdate();
	}

	CF_InputBindings GetBindings() 
	{
		return m_CF_Bindings;
	}

	int GetRPCMin()
	{
		return -1;
	}

	int GetRPCMax()
	{
		return -1;
	}

	// Permanent Event

	void OnInit()
	{

	}

	// Event Registration

	void EnableUpdate()
	{
		Start();
	}

	void EnableMissionStart()
	{
		CF_Module_Manager.s_MissionStart.Add(this);
	}

	void EnableMissionFinish()
	{
		CF_Module_Manager.s_MissionFinish.Add(this);
	}

	void EnableMissionLoaded()
	{
		CF_Module_Manager.s_MissionLoaded.Add(this);
	}

	void EnableRPC()
	{
		m_CF_RPC_Minimum = GetRPCMin();
		m_CF_RPC_Maximum = GetRPCMax();

		if (m_CF_RPC_Minimum == -1 || m_CF_RPC_Maximum == -1) return;

		CF_Module_Manager.s_RPC.Add(this);
	}

	void EnableWorldCleanup()
	{
		CF_Module_Manager.s_WorldCleanup.Add(this);
	}

	void EnableMPSessionStart()
	{
		CF_Module_Manager.s_MPSessionStart.Add(this);
	}

	void EnableMPSessionPlayerReady()
	{
		CF_Module_Manager.s_MPSessionPlayerReady.Add(this);
	}

	void EnableMPSessionFail()
	{
		CF_Module_Manager.s_MPSessionFail.Add(this);
	}

	void EnableMPSessionEnd()
	{
		CF_Module_Manager.s_MPSessionEnd.Add(this);
	}

	void EnableMPConnectAbort()
	{
		CF_Module_Manager.s_MPConnectAbort.Add(this);
	}

	void EnableMPConnectionLost()
	{
		CF_Module_Manager.s_MPConnectionLost.Add(this);
	}

	void EnableRespawn()
	{
		CF_Module_Manager.s_Respawn.Add(this);
	}

	// Events

	/**
	 * @note Automatically registers when 'Bind' is called
	 */
	protected override void OnUpdate(float dt)
	{
		m_CF_Bindings.Update(dt);

		super.OnUpdate(dt);
	}
	
	void OnMissionStart();
	
	void OnMissionFinish();
	
	void OnMissionLoaded();

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx);

	/**
	 * @brief See: WorldCleaupEventTypeID
	 */
	void OnWorldCleanup();

	/**
	 * @brief See: MPSessionStartEventTypeID
	 */
	void OnMPSessionStart();

	/**
	 * @brief See: MPSessionPlayerReadyEventTypeID
	 */
	void OnMPSessionPlayerReady();

	/**
	 * @brief See: MPSessionFailEventTypeID
	 */
	void OnMPSessionFail();

	/**
	 * @brief See: MPSessionEndEventTypeID
	 */
	void OnMPSessionEnd();

	/**
	 * @brief See: ConnectingAbortEventTypeID
	 */
	void OnMPConnectAbort();

	/**
	 * @brief See: MPConnectionLostEventTypeID
	 */
	void OnMPConnectionLost(int duration);

	/**
	 * @brief See: RespawnEventTypeID
	 */
	void OnRespawn(int time);

	// FALLBACKS

	void Error_Deprecated(string oldFunc, string newFunc)
	{
		Error(ClassName() + "::" + oldFunc + " is deprecated. Use " + ClassName() + "::" + newFunc + " instead.");
	}

	void Error_Removed(string oldFunc)
	{
		Error(ClassName() + "::" + oldFunc + " is deprecated and has no replacement.");
	}
	
	bool IsServer()
	{
		Error_Removed("IsServer");

		return true;
	}

	bool IsClient()
	{
		Error_Removed("IsClient");

		return true;
	}
};
