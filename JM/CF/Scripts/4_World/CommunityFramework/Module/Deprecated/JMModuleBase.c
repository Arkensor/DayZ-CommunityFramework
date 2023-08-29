/**
 * @class JMModuleBase
 * 
 * @deprecated
 */
class JMModuleBase : CF_ModuleWorld
{
	/**
	 * Any module that inherits from 'JMModuleBase' probably expects all events to be enabled
	 */
	override void Init()
	{
		EnableUpdate();
		EnableMissionStart();
		EnableMissionFinish();
		EnableMissionLoaded();
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
		EnableRPC();
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

		GetModuleManager().NP_InitModule(this);

		RegisterKeyMouseBindings();

		super.Init();
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

	override void OnRPC(Class sender, CF_EventArgs args)
	{
		super.OnRPC(sender, args);

		auto rpc = CF_EventRPCArgs.Cast(args);
		OnRPC(rpc.Sender, rpc.Target, rpc.ID, rpc.Context);
	}

	override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);

		OnMissionStart();
	}

	override void OnMissionFinish(Class sender, CF_EventArgs args)
	{
		super.OnMissionFinish(sender, args);

		OnMissionFinish();
	}

	override void OnMissionLoaded(Class sender, CF_EventArgs args)
	{
		super.OnMissionLoaded(sender, args);

		OnMissionLoaded();
	}

	override void OnUpdate(Class sender, CF_EventArgs args)
	{
		super.OnUpdate(sender, args);

		auto update = CF_EventUpdateArgs.Cast(args);
		OnUpdate(update.DeltaTime);
	}

	override void OnSettingsChanged(Class sender, CF_EventArgs args)
	{
		super.OnSettingsChanged(sender, args);

		OnSettingsUpdated();
	}

	override void OnPermissionsChanged(Class sender, CF_EventArgs args)
	{
		super.OnPermissionsChanged(sender, args);

		OnClientPermissionsUpdated();
	}

	override void OnWorldCleanup(Class sender, CF_EventArgs args)
	{
		super.OnWorldCleanup(sender, args);

		OnWorldCleanup();
	}

	override void OnMPSessionStart(Class sender, CF_EventArgs args)
	{
		super.OnMPSessionStart(sender, args);

		OnMPSessionStart();
	}

	override void OnMPSessionPlayerReady(Class sender, CF_EventArgs args)
	{
		super.OnMPSessionPlayerReady(sender, args);

		OnMPSessionPlayerReady();
	}

	override void OnMPSessionFail(Class sender, CF_EventArgs args)
	{
		super.OnMPSessionFail(sender, args);

		OnMPSessionFail();
	}

	override void OnMPSessionEnd(Class sender, CF_EventArgs args)
	{
		super.OnMPSessionEnd(sender, args);

		OnMPSessionEnd();
	}

	override void OnMPConnectAbort(Class sender, CF_EventArgs args)
	{
		super.OnMPConnectAbort(sender, args);

		OnMPConnectAbort();
	}

	override void OnMPConnectionLost(Class sender, CF_EventArgs args)
	{
		super.OnMPConnectionLost(sender, args);

		OnMPConnectionLost(CF_EventTimeArgs.Cast(args).Time);
	}

	override void OnRespawn(Class sender, CF_EventArgs args)
	{
		super.OnRespawn(sender, args);

		OnRespawn(CF_EventTimeArgs.Cast(args).Time);
	}

	override void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		super.OnInvokeConnect(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnInvokeConnect(cArgs.Player, cArgs.Identity);
	}

	override void OnInvokeDisconnect(Class sender, CF_EventArgs args)
	{
		super.OnInvokeDisconnect(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnInvokeDisconnect(cArgs.Player);
	}

	override void OnClientNew(Class sender, CF_EventArgs args)
	{
		super.OnClientNew(sender, args);

		auto cArgs = CF_EventNewPlayerArgs.Cast(args);
		OnClientNew(cArgs.Player, cArgs.Identity, cArgs.Position, cArgs.Context);
	}

	override void OnClientRespawn(Class sender, CF_EventArgs args)
	{
		super.OnClientRespawn(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnClientRespawn(cArgs.Player, cArgs.Identity);
	}

	override void OnClientReady(Class sender, CF_EventArgs args)
	{
		super.OnClientReady(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnClientReady(cArgs.Player, cArgs.Identity);
	}

	override void OnClientPrepare(Class sender, CF_EventArgs args)
	{
		super.OnClientPrepare(sender, args);

		auto cArgs = CF_EventPlayerPrepareArgs.Cast(args);
		OnClientPrepare(cArgs.Identity, cArgs.UseDatabase, cArgs.Position, cArgs.Yaw, cArgs.PreloadTimeout);
	}

	override void OnClientReconnect(Class sender, CF_EventArgs args)
	{
		super.OnClientReconnect(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnClientReconnect(cArgs.Player, cArgs.Identity);
	}

	override void OnClientLogout(Class sender, CF_EventArgs args)
	{
		super.OnClientLogout(sender, args);

		auto cArgs = CF_EventPlayerDisconnectedArgs.Cast(args);
		OnClientLogout(cArgs.Player, cArgs.Identity, cArgs.LogoutTime, cArgs.AuthFailed);
	}

	override void OnClientDisconnect(Class sender, CF_EventArgs args)
	{
		super.OnClientDisconnect(sender, args);

		auto cArgs = CF_EventPlayerDisconnectedArgs.Cast(args);
		OnClientDisconnect(cArgs.Player, cArgs.Identity, cArgs.UID);
	}

	override void OnClientLogoutCancelled(Class sender, CF_EventArgs args)
	{
		super.OnClientLogoutCancelled(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);
		OnClientLogoutCancelled(cArgs.Player);
	}

	// Old Events
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx);
	void OnMissionStart();
	void OnMissionFinish();
	void OnMissionLoaded();
	void OnUpdate(float timeslice);
	void OnSettingsUpdated();
	void OnClientPermissionsUpdated();
	void OnPermissionsChanged();
	void OnWorldCleanup();
	void OnMPSessionStart();
	void OnMPSessionPlayerReady();
	void OnMPSessionFail();
	void OnMPSessionEnd();
	void OnMPConnectAbort();
	void OnMPConnectionLost(int duration);
	void OnRespawn(int time);
	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity);
	void OnInvokeDisconnect(PlayerBase player);
	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx);
	void OnClientRespawn(PlayerBase player, PlayerIdentity identity);
	void OnClientReady(PlayerBase player, PlayerIdentity identity);
	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout);
	void OnClientReconnect(PlayerBase player, PlayerIdentity identity);
	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed);
	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid);
	void OnClientLogoutCancelled(PlayerBase player);

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
