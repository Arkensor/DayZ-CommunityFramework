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

	// Yikes ref
	ref JMModuleBase GetModule(typename type)
	{
		return JMModuleBase.Cast(CF_ModuleCoreManager.Get(type));
	}

	// Yikes ref
	protected void InitModule(ref JMModuleBase module)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "InitModule").Add(module);
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
		CF_ModuleWorldManager.OnInvokeConnect(player, identity);
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_ModuleWorldManager.OnInvokeDisconnect(player);
	}

	void OnClientNew(out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		CF_ModuleWorldManager.OnClientNew(player, identity, pos, ctx);
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientReady(player, identity);
	}

	void OnClientPrepare(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
		CF_ModuleWorldManager.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientReconnect(player, identity);
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldManager.OnClientRespawn(player, identity);
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		CF_ModuleWorldManager.OnClientLogout(player, identity, logoutTime, authFailed);
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		CF_ModuleWorldManager.OnClientDisconnect(player, identity, uid);
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		CF_ModuleWorldManager.OnClientLogoutCancelled(player);
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
