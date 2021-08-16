class JMModuleManager: JMModuleManagerBase
{
	ref array< JMModuleBase > m_ModuleList = new array< JMModuleBase >();

	void ConstructModules( JMModuleConstructorBase construct )
	{
	}

	ref JMModuleBase GetModule( typename type )
	{
		return JMModuleBase.Cast(CF_Module_Manager.Get( type ));
	}

	override void _InitModule( CF_Module module )
	{
		JMModuleBase modd = JMModuleBase.Cast(module);
		if (!modd) return;
		
		InitModule(modd);
	}

	protected void InitModule( ref JMModuleBase module )
	{
	}
	
	void OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity );

	void OnInvokeConnect( PlayerBase player, PlayerIdentity identity );

	void OnInvokeDisconnect( PlayerBase player );

	void OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx );

	void OnClientReady( PlayerBase player, PlayerIdentity identity );

	void OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout );

	void OnClientReconnect( PlayerBase player, PlayerIdentity identity );

	void OnClientRespawn( PlayerBase player, PlayerIdentity identity );

	void OnClientLogout( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed );

	void OnClientDisconnect( PlayerBase player, PlayerIdentity identity, string uid );

	void OnClientLogoutCancelled( PlayerBase player );
}

static JMModuleManager GetModuleManager()
{
	return JMModuleManager.Cast(g_cf_ModuleManager);
}

static void CreateModuleManager( JMModuleConstructorBase construct )
{
	JMModuleManager manager = new JMModuleManager;

	manager.ConstructModules( construct );
	manager.InitModules();

	g_cf_ModuleManager = manager;
}
