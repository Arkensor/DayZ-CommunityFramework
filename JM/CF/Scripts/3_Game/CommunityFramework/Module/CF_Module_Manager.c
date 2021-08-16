class CF_Module_Manager
{
	static ref CF_Module_Manager s_Instance = new CF_Module_Manager();

	static autoptr map<typename, ref CF_Module> s_ModuleMap = new map<typename, ref CF_Module>();

	static ref CF_Module_Event s_MissionStart = new CF_Module_Event();
	static ref CF_Module_Event s_MissionFinish = new CF_Module_Event();
	static ref CF_Module_Event s_MissionLoaded = new CF_Module_Event();
	static ref CF_Module_Event s_RPC = new CF_Module_Event();
	static ref CF_Module_Event s_WorldCleanup = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionStart = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionPlayerReady = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionFail = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionEnd = new CF_Module_Event();
	static ref CF_Module_Event s_MPConnectAbort = new CF_Module_Event();
	static ref CF_Module_Event s_MPConnectionLost = new CF_Module_Event();
	static ref CF_Module_Event s_Respawn = new CF_Module_Event();

	/**
	 * Load all modules on game start-up. Once registered a module can't be removed.
	 */
	static void RegisterModule(typename type)
	{
		if (s_ModuleMap.Contains(type)) return;

		CF_Module module = CF_Module.Cast(type.Spawn());
		s_ModuleMap.Insert(type, module);

		module.OnInit();
	}

	static CF_Module Get(typename type)
	{
		return s_ModuleMap[type];
	}

	/**
	 * @brief Deprecated
	 */
	static CF_Module GetModule(typename type)
	{
		return s_ModuleMap[type];
	}

	static CF_Module Get(string type)
	{
		return s_ModuleMap[type.ToType()];
	}

	static void OnMissionStart()
	{
		s_MissionStart.OnMissionStart();
	}

	static void OnMissionFinish()
	{
		s_MissionFinish.OnMissionFinish();
	}

	static void OnMissionLoaded()
	{
		s_MissionLoaded.OnMissionLoaded();
	}

	static void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		s_RPC.OnRPC(sender, target, rpc_type, ctx);
	}

	static void OnWorldCleanup()
	{
		s_WorldCleanup.OnWorldCleanup();
	}

	static void OnMPSessionStart()
	{
		s_MPSessionStart.OnMPSessionStart();
	}

	static void OnMPSessionPlayerReady()
	{
		s_MPSessionPlayerReady.OnMPSessionPlayerReady();
	}

	static void OnMPSessionFail()
	{
		s_MPSessionFail.OnMPSessionFail();
	}

	static void OnMPSessionEnd()
	{
		s_MPSessionEnd.OnMPSessionEnd();
	}

	static void OnMPConnectAbort()
	{
		s_MPConnectAbort.OnMPConnectAbort();
	}

	static void OnMPConnectionLost(int duration)
	{
		s_MPConnectionLost.OnMPConnectionLost(duration);
	}

	static void OnRespawn(int time)
	{
		s_Respawn.OnRespawn(time);
	}
};

static CF_Module_Manager GetModuleManager()
{
	return CF_Module_Manager.s_Instance;
}