class CF_ModuleCore : Managed
{
	static bool s_PreventInput = false;

	int m_CF_GameFlag;

	void CF_ModuleCore()
	{
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

	// Events

	void OnMissionStart();

	void OnMissionFinish();

	void OnMissionLoaded();

	void OnUpdate(float timeslice);

	void OnSettingsChanged();

	void OnPermissionsChanged();

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
		CF_Log.Info(ClassName() + "::" + oldFunc + " is deprecated. Use " + ClassName() + "::" + newFunc + " instead.");
	}

	void Error_Removed(string oldFunc)
	{
		CF_Log.Info(ClassName() + "::" + oldFunc + " is deprecated and has no replacement.");
	}
};
