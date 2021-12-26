static autoptr CF_ModuleCoreManager g_CF_Module_Manager;

class CF_ModuleCoreManager
{
	static ref array<string> s_ModuleNames = new array<string>();

	static ref map<typename, CF_ModuleCore> s_ModulesMap = new map<typename, CF_ModuleCore>();
	static ref array<ref CF_ModuleCore> s_Modules = new array<ref CF_ModuleCore>();

	static bool s_IsCreated;

	static ref CF_ModuleCoreEvent s_MissionStart = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MissionFinish = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MissionLoaded = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_Update = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_SettingsChanged = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_PermissionsChanged = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_WorldCleanup = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPSessionStart = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPSessionPlayerReady = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPSessionFail = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPSessionEnd = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPConnectAbort = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_MPConnectionLost = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_Respawn = new CF_ModuleCoreEvent();

	static int s_GameFlag;

	static void _OnCreate()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("Create");
#endif

		_OnDestroy();

		g_CF_Module_Manager = new CF_ModuleCoreManager();

		s_IsCreated = true;

		for (int i = 0; i < s_ModuleNames.Count(); i++)
		{
			_Create(s_ModuleNames[i]);
		}
	}

	static void _OnDestroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("Create");
#endif

		s_ModulesMap.Clear();
		s_Modules.Clear();

		s_IsCreated = false;
	}

	/**
	 * @brief Inserts the module typename into the list of modules to create, creates if already instantiated
	 */
	static void _Insert(typename type)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Insert").Add(type);
#endif

		string className = type.ToString();
		s_ModuleNames.Insert(className);

		if (s_IsCreated)
		{
			_Create(className);
		}
	}

	/**
	 * @brief Creates the module from the name of the class
	 */
	static void _Create(string className)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1("Create").Add(className);
#endif

		CF_ModuleCore module;
		if (!Class.CastTo(module, className.ToType().Spawn()))
		{
			return;
		}

		if (s_ModulesMap.Contains(module.GetType()))
		{
			return;
		}

		s_ModulesMap.Insert(module.GetType(), module);
		s_Modules.Insert(module);

		module.m_CF_GameFlag = 0;
		if (module.IsClient())
		{
			module.m_CF_GameFlag |= 0x0F;
		}

		if (module.IsServer())
		{
			module.m_CF_GameFlag |= 0xF0;
		}

		module.OnInit();
	}

	static CF_ModuleCore Get(typename type)
	{
		return s_ModulesMap[type];
	}

	/**
	 * @brief Deprecated
	 */
	static CF_ModuleCore GetModule(typename type)
	{
		return s_ModulesMap[type];
	}

	static CF_ModuleCore Get(string type)
	{
		return s_ModulesMap[type.ToType()];
	}

	static CF_ModuleCore Get(int index)
	{
		return s_Modules[index];
	}

	static int Count()
	{
		return s_Modules.Count();
	}

	// EVENTS

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
