class JMModuleManagerBase
{
    protected bool m_PreventModuleBindings;

	void JMModuleManagerBase()
	{
		//GetLogger().Log( "JMModuleManagerBase::JMModuleManagerBase()", "JM_COT_ModuleFramework" );
	}

	void ~JMModuleManagerBase()
	{
		//GetLogger().Log( "JMModuleManagerBase::~JMModuleManagerBase()", "JM_COT_ModuleFramework" );
	}

    bool IsPreventingModuleBindings()
    {
        return m_PreventModuleBindings;
    }

    void SetPreventModuleBindings( bool prevent )
    {
        m_PreventModuleBindings = prevent;
    }

	void RegisterModules()
	{
		//GetLogger().Log( "JMModuleManagerBase::RegisterModules()", "JM_COT_ModuleFramework" );
	}

	void Print_DumpModules()
	{
        //GetLogger().Log( "JMModuleManagerBase::Print_DumpModules()", "JM_COT_ModuleFramework" );
    }

	void OnSettingsUpdated()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnSettingsUpdated()", "JM_COT_ModuleFramework" );
	}

	void OnInit()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnInit()", "JM_COT_ModuleFramework" );
	}

	void OnMissionStart()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMissionStart()", "JM_COT_ModuleFramework" );
	}

	void OnMissionFinish()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMissionFinish()", "JM_COT_ModuleFramework" );
	}

	void OnMissionLoaded()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMissionLoaded()", "JM_COT_ModuleFramework" );
	}

	void OnUpdate( float timeslice )
	{
		//GetLogger().Log( "JMModuleManagerBase::OnUpdate()", "JM_COT_ModuleFramework" );
	}

	bool OnWorldCleanup()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnWorldCleanup()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnMPSessionStart()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPSessionStart()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnMPSessionPlayerReady()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPSessionPlayerReady()", "JM_COT_ModuleFramework" );
        return false;
    }

	bool OnMPSessionFail()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPSessionFail()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnMPSessionEnd()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPSessionEnd()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnMPConnectAbort()
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPConnectAbort()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnMPConnectionLost( int duration )
	{
		//GetLogger().Log( "JMModuleManagerBase::OnMPConnectionLost()", "JM_COT_ModuleFramework" );
        return false;
	}

	bool OnRespawn( int time )
	{
		//GetLogger().Log( "JMModuleManagerBase::OnRespawn()", "JM_COT_ModuleFramework" );
        return false;
	}
}

ref JMModuleManagerBase g_cot_ModuleManager = NULL;

static void DestroyModuleManager()
{
	delete g_cot_ModuleManager;
}

static bool ModuleManagerExists()
{
	return g_cot_ModuleManager != NULL;
}