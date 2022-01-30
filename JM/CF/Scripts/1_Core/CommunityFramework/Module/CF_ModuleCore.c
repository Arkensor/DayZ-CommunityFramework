class CF_ModuleCore : Managed
{
	static bool s_PreventInput = false;

	int m_CF_GameFlag;

	void CF_ModuleCore()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_ModuleCore");
#endif
	}

	void ~CF_ModuleCore()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_ModuleCore");
#endif
	}

	bool IsServer()
	{
		return true;
	}

	bool IsClient()
	{
		return true;
	}

	typename GetType()
	{
		return Type();
	}

	// Permanent Event

	void Init()
	{
		OnInit();
	}

	void OnInit()
	{
	}

	// Event Registration

	void EnableUpdate()
	{
		CF_ModuleCoreManager.s_Update.Add(this);
	}

	void EnableMissionStart()
	{
		CF_ModuleCoreManager.s_MissionStart.Add(this);
	}

	void EnableMissionFinish()
	{
		CF_ModuleCoreManager.s_MissionFinish.Add(this);
	}

	void EnableMissionLoaded()
	{
		CF_ModuleCoreManager.s_MissionLoaded.Add(this);
	}

	void EnableSettingsChanged()
	{
		CF_ModuleCoreManager.s_SettingsChanged.Add(this);
	}

	void EnablePermissionsChanged()
	{
		CF_ModuleCoreManager.s_PermissionsChanged.Add(this);
	}

	void EnableWorldCleanup()
	{
		CF_ModuleCoreManager.s_WorldCleanup.Add(this);
	}

	void EnableMPSessionStart()
	{
		CF_ModuleCoreManager.s_MPSessionStart.Add(this);
	}

	void EnableMPSessionPlayerReady()
	{
		CF_ModuleCoreManager.s_MPSessionPlayerReady.Add(this);
	}

	void EnableMPSessionFail()
	{
		CF_ModuleCoreManager.s_MPSessionFail.Add(this);
	}

	void EnableMPSessionEnd()
	{
		CF_ModuleCoreManager.s_MPSessionEnd.Add(this);
	}

	void EnableMPConnectAbort()
	{
		CF_ModuleCoreManager.s_MPConnectAbort.Add(this);
	}

	void EnableMPConnectionLost()
	{
		CF_ModuleCoreManager.s_MPConnectionLost.Add(this);
	}

	void EnableRespawn()
	{
		CF_ModuleCoreManager.s_Respawn.Add(this);
	}

	void EnableLoginTime()
	{
		CF_ModuleCoreManager.s_LoginTime.Add(this);
	}

	void EnableLoginStatus()
	{
		CF_ModuleCoreManager.s_LoginStatus.Add(this);
	}

	void EnableLogout()
	{
		CF_ModuleCoreManager.s_Logout.Add(this);
	}

	void EnableChat()
	{
		CF_ModuleCoreManager.s_Chat.Add(this);
	}

	// Events

	void OnMissionStart(Class sender, CF_EventArgs args);

	void OnMissionFinish(Class sender, CF_EventArgs args);

	void OnMissionLoaded(Class sender, CF_EventArgs args);

	void OnUpdate(Class sender, CF_EventArgs args);

	void OnSettingsChanged(Class sender, CF_EventArgs args);

	void OnPermissionsChanged(Class sender, CF_EventArgs args);

	/**
	 * @brief See: WorldCleaupEventTypeID
	 */
	void OnWorldCleanup(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MPSessionStartEventTypeID
	 */
	void OnMPSessionStart(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MPSessionPlayerReadyEventTypeID
	 */
	void OnMPSessionPlayerReady(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MPSessionFailEventTypeID
	 */
	void OnMPSessionFail(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MPSessionEndEventTypeID
	 */
	void OnMPSessionEnd(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ConnectingAbortEventTypeID
	 */
	void OnMPConnectAbort(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MPConnectionLostEventTypeID
	 */
	void OnMPConnectionLost(Class sender, CF_EventArgs args);

	/**
	 * @brief See: RespawnEventTypeID
	 */
	void OnRespawn(Class sender, CF_EventArgs args);

	/**
	 * @brief See: LoginTimeEventTypeID
	 */
	void OnLoginTime(Class sender, CF_EventArgs args);
	
	/**
	 * @brief See: LoginStatusEventTypeID
	 */
	void OnLoginStatus(Class sender, CF_EventArgs args);
	
	/**
	 * @brief See: LogoutEventTypeID
	 */
	void OnLogout(Class sender, CF_EventArgs args);
	
	/**
	 * @brief See: ChatMessageEventTypeID
	 */
	void OnChat(Class sender, CF_EventArgs args);

	// FALLBACKS

	void Error_Deprecated(string oldFunc, string newFunc)
	{
		CF_Log.Info(ClassName() + "::" + oldFunc + " is deprecated. Use " + ClassName() + "::" + newFunc + " instead.");
	}

	void Error_Removed(string oldFunc)
	{
		CF_Log.Info(ClassName() + "::" + oldFunc + " is deprecated and has no replacement.");
	}
};
