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
	static ref CF_ModuleCoreEvent s_LoginTime = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_LoginStatus = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_Logout = new CF_ModuleCoreEvent();
	static ref CF_ModuleCoreEvent s_Chat = new CF_ModuleCoreEvent();

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

		module.Init();
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

	static void OnMissionStart(Class sender, CF_EventArgs args)
	{
		s_MissionStart.OnMissionStart(sender, args);
	}

	static void OnMissionFinish(Class sender, CF_EventArgs args)
	{
		s_MissionFinish.OnMissionFinish(sender, args);
	}

	static void OnMissionLoaded(Class sender, CF_EventArgs args)
	{
		s_MissionLoaded.OnMissionLoaded(sender, args);
	}

	static void OnSettingsChanged(Class sender, CF_EventArgs args)
	{
		s_SettingsChanged.OnSettingsChanged(sender, args);
	}

	static void OnPermissionsChanged(Class sender, CF_EventArgs args)
	{
		s_PermissionsChanged.OnPermissionsChanged(sender, args);
	}

	static void OnWorldCleanup(Class sender, CF_EventArgs args)
	{
		s_WorldCleanup.OnWorldCleanup(sender, args);
	}

	static void OnMPSessionStart(Class sender, CF_EventArgs args)
	{
		s_MPSessionStart.OnMPSessionStart(sender, args);
	}

	static void OnMPSessionPlayerReady(Class sender, CF_EventArgs args)
	{
		s_MPSessionPlayerReady.OnMPSessionPlayerReady(sender, args);
	}

	static void OnMPSessionFail(Class sender, CF_EventArgs args)
	{
		s_MPSessionFail.OnMPSessionFail(sender, args);
	}

	static void OnMPSessionEnd(Class sender, CF_EventArgs args)
	{
		s_MPSessionEnd.OnMPSessionEnd(sender, args);
	}

	static void OnMPConnectAbort(Class sender, CF_EventArgs args)
	{
		s_MPConnectAbort.OnMPConnectAbort(sender, args);
	}

	static void OnMPConnectionLost(Class sender, CF_EventArgs args)
	{
		s_MPConnectionLost.OnMPConnectionLost(sender, args);
	}

	static void OnRespawn(Class sender, CF_EventArgs args)
	{
		s_Respawn.OnRespawn(sender, args);
	}

	static void OnLoginTime(Class sender, CF_EventArgs args)
	{
		s_LoginTime.OnLoginTime(sender, args);
	}

	static void OnLoginStatus(Class sender, CF_EventArgs args)
	{
		s_LoginStatus.OnLoginStatus(sender, args);
	}

	static void OnLogout(Class sender, CF_EventArgs args)
	{
		s_Logout.OnLogout(sender, args);
	}

	static void OnChat(Class sender, CF_EventArgs args)
	{
		s_Chat.OnChat(sender, args);
	}
};
