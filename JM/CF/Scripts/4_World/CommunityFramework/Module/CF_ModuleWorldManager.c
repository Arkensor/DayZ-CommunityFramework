class CF_ModuleWorldManager
{
	static autoptr CF_ModuleWorldEvent s_InvokeConnect = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_InvokeDisconnect = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientNew = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientRespawn = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientReady = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientPrepare = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientReconnect = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientLogout = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientDisconnect = new CF_ModuleWorldEvent();
	static autoptr CF_ModuleWorldEvent s_ClientLogoutCancelled = new CF_ModuleWorldEvent();

	static void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		s_InvokeConnect.OnInvokeConnect(sender, args);

		delete args;
	}

	static void OnInvokeDisconnect(Class sender, CF_EventArgs args)
	{
		s_InvokeDisconnect.OnInvokeDisconnect(sender, args);

		delete args;
	}

	static void OnClientNew(Class sender, CF_EventArgs args)
	{
		s_ClientNew.OnClientNew(sender, args);

		delete args;
	}

	static void OnClientRespawn(Class sender, CF_EventArgs args)
	{
		s_ClientRespawn.OnClientRespawn(sender, args);

		delete args;
	}

	static void OnClientReady(Class sender, CF_EventArgs args)
	{
		s_ClientReady.OnClientReady(sender, args);

		delete args;
	}

	static void OnClientPrepare(Class sender, CF_EventArgs args)
	{
		s_ClientPrepare.OnClientPrepare(sender, args);

		delete args;
	}

	static void OnClientReconnect(Class sender, CF_EventArgs args)
	{
		s_ClientReconnect.OnClientReconnect(sender, args);

		delete args;
	}

	static void OnClientLogout(Class sender, CF_EventArgs args)
	{
		s_ClientLogout.OnClientLogout(sender, args);

		delete args;
	}

	static void OnClientDisconnect(Class sender, CF_EventArgs args)
	{
		s_ClientDisconnect.OnClientDisconnect(sender, args);

		delete args;
	}

	static void OnClientLogoutCancelled(Class sender, CF_EventArgs args)
	{
		s_ClientLogoutCancelled.OnClientLogoutCancelled(sender, args);

		delete args;
	}
};
