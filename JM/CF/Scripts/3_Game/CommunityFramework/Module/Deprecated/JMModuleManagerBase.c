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
		CF_ModuleCoreManager.OnSettingsChanged(this, CF_EventArgs.Empty);
	}

	void OnClientPermissionsUpdated()
	{
		CF_ModuleCoreManager.OnPermissionsChanged(this, CF_EventArgs.Empty);
	}

	void OnInit()
	{
		// does nothing
	}

	void OnMissionStart()
	{
		CF_ModuleCoreManager.OnMissionStart(this, CF_EventArgs.Empty);
	}

	void OnMissionFinish()
	{
		CF_ModuleCoreManager.OnMissionFinish(this, CF_EventArgs.Empty);
	}

	void OnMissionLoaded()
	{
		CF_ModuleCoreManager.OnMissionLoaded(this, CF_EventArgs.Empty);
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		auto args = new CF_EventRPCArgs();
		args.Sender = sender;
		args.Target = target;
		args.ID = rpc_type;
		args.Context = ctx;
		CF_ModuleGameManager.OnRPC(this, args);
	}

	void OnUpdate(float timeslice)
	{
		CF_ModuleGameManager.OnUpdate(this, new CF_EventUpdateArgs(timeslice));
	}

	void OnWorldCleanup()
	{
		CF_ModuleCoreManager.OnWorldCleanup(this, CF_EventArgs.Empty);
	}

	void OnMPSessionStart()
	{
		CF_ModuleCoreManager.OnMPSessionStart(this, CF_EventArgs.Empty);
	}

	void OnMPSessionPlayerReady()
	{
		CF_ModuleCoreManager.OnMPSessionPlayerReady(this, CF_EventArgs.Empty);
	}

	void OnMPSessionFail()
	{
		CF_ModuleCoreManager.OnMPSessionFail(this, CF_EventArgs.Empty);
	}

	void OnMPSessionEnd()
	{
		CF_ModuleCoreManager.OnMPSessionEnd(this, CF_EventArgs.Empty);
	}

	void OnMPConnectAbort()
	{
		CF_ModuleCoreManager.OnMPConnectAbort(this, CF_EventArgs.Empty);
	}

	void OnMPConnectionLost(int duration)
	{
		CF_ModuleCoreManager.OnMPConnectionLost(this, new CF_EventTimeArgs(duration));
	}

	void OnRespawn(int time)
	{
		CF_ModuleCoreManager.OnRespawn(this, new CF_EventTimeArgs(time));
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
