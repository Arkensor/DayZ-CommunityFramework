class CF_Module_WorldManager
{
	static ref CF_Module_WorldEvent s_InvokeConnect = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_InvokeDisconnect = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientNew = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientRespawn = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientReady = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientPrepare = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientReconnect = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientLogout = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientDisconnect = new CF_Module_WorldEvent();
	static ref CF_Module_WorldEvent s_ClientLogoutCancelled = new CF_Module_WorldEvent();

	static void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		s_InvokeConnect.OnInvokeConnect(player, identity);
	}

	static void OnInvokeDisconnect(PlayerBase player)
	{
		s_InvokeDisconnect.OnInvokeDisconnect(player);
	}

	static void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		s_ClientNew.OnClientNew(player, identity, pos, ctx);
	}

	static void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		s_ClientRespawn.OnClientRespawn(player, identity);
	}

	static void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		s_ClientReady.OnClientReady(player, identity);
	}

	static void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout)
	{
		s_ClientPrepare.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
	}

	static void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		s_ClientReconnect.OnClientReconnect(player, identity);
	}

	static void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		s_ClientLogout.OnClientLogout(player, identity, logoutTime, authFailed);
	}

	static void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		s_ClientDisconnect.OnClientDisconnect(player, identity, uid);
	}

	static void OnClientLogoutCancelled(PlayerBase player)
	{
		s_ClientLogoutCancelled.OnClientLogoutCancelled(player);
	}
};
