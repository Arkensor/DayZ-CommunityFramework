static autoptr CF_Module_Manager g_CF_Module_Manager;

class CF_Module_Manager
{
	static autoptr map<typename, ref CF_Module> s_ModuleMap = new map<typename, ref CF_Module>();

	static ref CF_Module_Event s_MissionStart = new CF_Module_Event();
	static ref CF_Module_Event s_MissionFinish = new CF_Module_Event();
	static ref CF_Module_Event s_MissionLoaded = new CF_Module_Event();
	static ref CF_Module_Event s_Update = new CF_Module_Event();
	static ref CF_Module_Event s_RPC = new CF_Module_Event();
	static ref CF_Module_Event s_SettingsChanged = new CF_Module_Event();
	static ref CF_Module_Event s_PermissionsChanged = new CF_Module_Event();
	static ref CF_Module_Event s_WorldCleanup = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionStart = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionPlayerReady = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionFail = new CF_Module_Event();
	static ref CF_Module_Event s_MPSessionEnd = new CF_Module_Event();
	static ref CF_Module_Event s_MPConnectAbort = new CF_Module_Event();
	static ref CF_Module_Event s_MPConnectionLost = new CF_Module_Event();
	static ref CF_Module_Event s_Respawn = new CF_Module_Event();
	
	static int s_GameFlag;

	ref CF_Timer m_Timer;
	
	private void CF_Module_Manager()
	{
		m_Timer = CF_Timer.Create(this, "Update");
	}
	
	[CF_EventSubscriber(CF_Module_Manager._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		g_CF_Module_Manager = new CF_Module_Manager();
	}

	void Update(CF_TimerBase timer, float timeslice)
	{
		s_GameFlag = 0xFF;
		if (GetGame().IsMultiplayer())
		{
			s_GameFlag = 0x0F;
			if (GetGame().IsServer()) s_GameFlag = 0xF0;
		}

		s_Update.OnUpdate(timeslice);
	}

	/**
	 * Load all modules on game start-up. Once registered a module can't be removed.
	 */
	static void RegisterModule(typename type)
	{
		if (s_ModuleMap.Contains(type)) return;

		CF_Module module = CF_Module.Cast(type.Spawn());
		s_ModuleMap.Insert(type, module);

		module.m_CF_GameFlag = 0;
		if (module.IsClient()) module.m_CF_GameFlag |= 0x0F;
		if (module.IsServer()) module.m_CF_GameFlag |= 0xF0;

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

	static void OnSettingsChanged()
	{
		s_SettingsChanged.OnSettingsChanged();
	}

	static void OnPermissionsChanged()
	{
		s_PermissionsChanged.OnPermissionsChanged();
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
