class JMModuleManagerBase
{
	protected bool m_PreventModuleBindings;

	void JMModuleManagerBase()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "JMModuleManagerBase");
		#endif
	}

	void ~JMModuleManagerBase()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~JMModuleManagerBase");
		#endif
	}

	bool IsPreventingModuleBindings()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "IsPreventingModuleBindings");
		#endif
		return m_PreventModuleBindings;
	}

	void SetPreventModuleBindings( bool prevent )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetPreventModuleBindings").Add(prevent);
		#endif

		m_PreventModuleBindings = prevent;
	}

	void InitModules()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "InitModules");
		#endif
	}

	void Print_DumpModules()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Print_DumpModules");
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

	void OnUpdate( float timeslice )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnUpdate").Add(timeslice);
		#endif
	}

	void OnWorldCleanup()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnWorldCleanup");
		#endif
	}

	void OnMPSessionStart()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionStart");
		#endif
	}

	void OnMPSessionPlayerReady()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionPlayerReady");
		#endif
	}

	void OnMPSessionFail()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionFail");
		#endif
	}

	void OnMPSessionEnd()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPSessionEnd");
		#endif
	}

	void OnMPConnectAbort()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnMPConnectAbort");
		#endif
	}

	void OnMPConnectionLost( int duration )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnMPConnectionLost").Add(duration);
		#endif
	}

	void OnRespawn( int time )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnRespawn").Add(time);
		#endif
	}
}

ref JMModuleManagerBase g_cf_ModuleManager = NULL;

static void DestroyModuleManager()
{
	delete g_cf_ModuleManager;
}

static bool ModuleManagerExists()
{
	return g_cf_ModuleManager != NULL;
}