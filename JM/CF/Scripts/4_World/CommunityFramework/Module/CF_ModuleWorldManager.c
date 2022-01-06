class CF_ModuleWorldManager
{
	static ref CF_ModuleWorldEvent s_InvokeConnect = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_InvokeDisconnect = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientNew = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientRespawn = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientReady = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientPrepare = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientReconnect = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientLogout = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientDisconnect = new CF_ModuleWorldEvent();
	static ref CF_ModuleWorldEvent s_ClientLogoutCancelled = new CF_ModuleWorldEvent();

	static void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		s_InvokeConnect.OnInvokeConnect(sender, args);
	}

	static void OnInvokeDisconnect(Class sender, CF_EventArgs args)
	{
		s_InvokeDisconnect.OnInvokeDisconnect(sender, args);
	}

	static void OnClientNew(Class sender, CF_EventArgs args)
	{
		s_ClientNew.OnClientNew(sender, args);
	}

	static void OnClientRespawn(Class sender, CF_EventArgs args)
	{
		s_ClientRespawn.OnClientRespawn(sender, args);
	}

	static void OnClientReady(Class sender, CF_EventArgs args)
	{
		s_ClientReady.OnClientReady(sender, args);
	}

	static void OnClientPrepare(Class sender, CF_EventArgs args)
	{
		s_ClientPrepare.OnClientPrepare(sender, args);
	}

	static void OnClientReconnect(Class sender, CF_EventArgs args)
	{
		s_ClientReconnect.OnClientReconnect(sender, args);
	}

	static void OnClientLogout(Class sender, CF_EventArgs args)
	{
		s_ClientLogout.OnClientLogout(sender, args);
	}

	static void OnClientDisconnect(Class sender, CF_EventArgs args)
	{
		s_ClientDisconnect.OnClientDisconnect(sender, args);
	}

	static void OnClientLogoutCancelled(Class sender, CF_EventArgs args)
	{
		s_ClientLogoutCancelled.OnClientLogoutCancelled(sender, args);
	}
};
