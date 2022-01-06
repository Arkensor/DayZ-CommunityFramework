/**
 * @class JMModuleManagerBase
 * 
 * @deprecated
 */
class JMModuleManagerBase
{
	protected bool m_PreventModuleBindings;

	bool IsPreventingModuleBindings()
	{
		m_PreventModuleBindings = CF_ModuleGame.s_PreventInput;
		return CF_ModuleGame.s_PreventInput;
	}

	void SetPreventModuleBindings(bool prevent)
	{
		CF_ModuleGame.s_PreventInput = prevent;
		m_PreventModuleBindings = CF_ModuleGame.s_PreventInput;
	}

	void InitModules()
	{
		// does nothing
	}

	void Print_DumpModules()
	{
		// does nothing
	}

	void OnSettingsUpdated()
	{
		CF_ModuleCoreManager.OnSettingsChanged();
	}

	void OnClientPermissionsUpdated()
	{
		CF_ModuleCoreManager.OnPermissionsChanged();
	}

	void OnInit()
	{
		// does nothing
	}

	void OnMissionStart()
	{
		CF_ModuleCoreManager.OnMissionStart();
	}

	void OnMissionFinish()
	{
		CF_ModuleCoreManager.OnMissionFinish();
	}

	void OnMissionLoaded()
	{
		CF_ModuleCoreManager.OnMissionLoaded();
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx)
	{
		CF_ModuleGameManager.OnRPC(sender, target, rpc_type, ctx);
	}

	void OnUpdate(float timeslice)
	{
		CF_ModuleGameManager.OnUpdate(timeslice);
	}

	void OnWorldCleanup()
	{
		CF_ModuleCoreManager.OnWorldCleanup();
	}

	void OnMPSessionStart()
	{
		CF_ModuleCoreManager.OnMPSessionStart();
	}

	void OnMPSessionPlayerReady()
	{
		CF_ModuleCoreManager.OnMPSessionPlayerReady();
	}

	void OnMPSessionFail()
	{
		CF_ModuleCoreManager.OnMPSessionFail();
	}

	void OnMPSessionEnd()
	{
		CF_ModuleCoreManager.OnMPSessionEnd();
	}

	void OnMPConnectAbort()
	{
		CF_ModuleCoreManager.OnMPConnectAbort();
	}

	void OnMPConnectionLost(int duration)
	{
		CF_ModuleCoreManager.OnMPConnectionLost(duration);
	}

	void OnRespawn(int time)
	{
		CF_ModuleCoreManager.OnRespawn(time);
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
