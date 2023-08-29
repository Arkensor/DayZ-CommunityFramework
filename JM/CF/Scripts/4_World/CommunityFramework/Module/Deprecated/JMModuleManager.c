/**
 * @class JMModuleManager
 * 
 * @deprecated
 */
class JMModuleManager : JMModuleManagerBase
{
	protected autoptr array<JMModuleBase> m_ModuleList;

	void JMModuleManager()
	{
		m_ModuleList = new array<JMModuleBase>();
	}

	JMModuleBase GetModule(typename type)
	{
		return JMModuleBase.Cast(CF_ModuleCoreManager.Get(type));
	}

	protected void InitModule(JMModuleBase module)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this).Add(module);
#endif

		m_ModuleList.Insert(module);
	}

	/**
	 * @note Can't remove protected from 'InitModule'' without compile errors
	 */
	void NP_InitModule(JMModuleBase module)
	{
		InitModule(module);
	}

	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnInvokeConnect(this, new CF_EventPlayerArgs(player, identity));
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_ModuleWorldManager.OnInvokeDisconnect(this, new CF_EventPlayerArgs(player));
	}

	void OnClientNew(out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		auto args = new CF_EventNewPlayerArgs(player, identity, pos, ctx);
		CF_ModuleWorldManager.OnClientNew(this, args);
		player = args.Player;
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientReady(this, new CF_EventPlayerArgs(player, identity));
	}

	void OnClientPrepare(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
		auto args = new CF_EventPlayerPrepareArgs();
		args.Identity = identity;
		args.UseDatabase = useDB;
		args.Position = pos;
		args.Yaw = yaw;
		args.PreloadTimeout = preloadTimeout;

		CF_ModuleWorldManager.OnClientPrepare(this, args);
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientReconnect(this, new CF_EventPlayerArgs(player, identity));
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientRespawn(this, new CF_EventPlayerArgs(player, identity));
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		auto args = new CF_EventPlayerDisconnectedArgs(player, identity);
		args.LogoutTime = logoutTime;
		args.AuthFailed = authFailed;

		CF_ModuleWorldManager.OnClientLogout(this, args);
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		auto args = new CF_EventPlayerDisconnectedArgs(player, identity);
		args.UID = uid;

		CF_ModuleWorldManager.OnClientDisconnect(this, args);
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		CF_ModuleWorldManager.OnClientLogoutCancelled(this, new CF_EventPlayerArgs(player));
	}
}

static JMModuleManager GetModuleManager()
{
	if (!g_JMModuleManager)
	{
		g_JMModuleManager = new JMModuleManager();
	}

	return g_JMModuleManager;
}

static ref JMModuleManager g_JMModuleManager;

static void CreateModuleManager(JMModuleConstructorBase construct)
{
}
