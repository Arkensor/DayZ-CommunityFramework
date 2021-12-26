class JMModuleBase : CF_ModuleWorld
{
	/**
	 * Any module that inherits from 'JMModuleBase' probably expects all events to be enabled
	 */
	override void OnInit()
	{
		super.OnInit();

		RegisterKeyMouseBindings();

		EnableUpdate();
		EnableMissionStart();
		EnableMissionFinish();
		EnableMissionLoaded();
		EnableRPC();
		EnableSettingsChanged();
		EnablePermissionsChanged();
		EnableWorldCleanup();
		EnableMPSessionStart();
		EnableMPSessionPlayerReady();
		EnableMPSessionFail();
		EnableMPSessionEnd();
		EnableMPConnectAbort();
		EnableMPConnectionLost();
		EnableRespawn();
		EnableInvokeConnect();
		EnableInvokeDisconnect();
		EnableClientNew();
		EnableClientRespawn();
		EnableClientReady();
		EnableClientPrepare();
		EnableClientLogoutReconnect();
		EnableClientLogout();
		EnableClientDisconnect();
		EnableClientLogoutCancelled();

		Init();
	}
	
	void Init()
	{
		RegisterKeyMouseBindings();
	}

	void Toggle()
	{
	}

	void PreventInput(bool prevent)
	{
	}

	string GetModuleName()
	{
		return ClassName();
	}

	typename GetModuleType()
	{
		return Type();
	}

	bool IsEnabled()
	{
		return true;
	}

	bool IsPreventingInput()
	{
		return false;
	}
	
	set<ref JMModuleBinding> GetBindings()
	{
		return new set<ref JMModuleBinding>();
	}

	void OnSettingsUpdated();

	void OnClientPermissionsUpdated();

	override void OnSettingsChanged()
	{
		OnSettingsUpdated();
	}

	override void OnPermissionsChanged()
	{
		OnClientPermissionsUpdated();
	}

	override void OnRPC(CF_ModuleRPC rpc, Serializer ctx)
	{
		super.OnRPC(rpc, ctx);

		OnRPC(rpc.Sender, rpc.Target, rpc.Type, ctx);
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx)
	{
	}

	void RegisterKeyMouseBindings() 
	{

	}

	void RegisterKeyMouseBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterKeyMouseBinding", "Bind");
	}

	void RegisterBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterBinding", "Bind");
	}
};
