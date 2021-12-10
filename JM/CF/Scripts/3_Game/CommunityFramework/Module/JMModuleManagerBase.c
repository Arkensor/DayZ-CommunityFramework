class JMModuleManagerBase
{
	protected bool m_PreventModuleBindings;

	void JMModuleManagerBase()
	{
	}

	void ~JMModuleManagerBase()
	{
	}

	bool IsPreventingModuleBindings()
	{
		return m_PreventModuleBindings;
	}

	void SetPreventModuleBindings( bool prevent )
	{
		m_PreventModuleBindings = prevent;
	}

	void InitModules()
	{
	}

	void Print_DumpModules()
	{
	}

	void OnSettingsUpdated()
	{
	}
	
	void OnClientPermissionsUpdated()
	{
	}

	void OnInit()
	{
	}

	void OnMissionStart()
	{
	}

	void OnMissionFinish()
	{
	}

	void OnMissionLoaded()
	{
	}
	
	void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx )
	{
	}

	void OnUpdate( float timeslice )
	{
	}

	void OnWorldCleanup()
	{
	}

	void OnMPSessionStart()
	{
	}

	void OnMPSessionPlayerReady()
	{
	}

	void OnMPSessionFail()
	{
	}

	void OnMPSessionEnd()
	{
	}

	void OnMPConnectAbort()
	{
	}

	void OnMPConnectionLost( int duration )
	{
	}

	void OnRespawn( int time )
	{
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