class CF_ModuleWorld : CF_ModuleGame
{
	void EnableInvokeConnect()
	{
		CF_ModuleWorldManager.s_InvokeConnect.Add(this);
	}

	void EnableInvokeDisconnect()
	{
		CF_ModuleWorldManager.s_InvokeDisconnect.Add(this);
	}

	void EnableClientNew()
	{
		CF_ModuleWorldManager.s_ClientNew.Add(this);
	}

	void EnableClientRespawn()
	{
		CF_ModuleWorldManager.s_ClientRespawn.Add(this);
	}

	void EnableClientReady()
	{
		CF_ModuleWorldManager.s_ClientReady.Add(this);
	}

	void EnableClientPrepare()
	{
		CF_ModuleWorldManager.s_ClientPrepare.Add(this);
	}

	void EnableClientLogoutReconnect()
	{
		CF_ModuleWorldManager.s_ClientReconnect.Add(this);
	}

	void EnableClientLogout()
	{
		CF_ModuleWorldManager.s_ClientLogout.Add(this);
	}

	void EnableClientDisconnect()
	{
		CF_ModuleWorldManager.s_ClientDisconnect.Add(this);
	}

	void EnableClientLogoutCancelled()
	{
		CF_ModuleWorldManager.s_ClientLogoutCancelled.Add(this);
	}

	/**
	 * @brief See: MissionServer::InvokeOnConnect
	 */
	void OnInvokeConnect(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MissionServer::InvokeOnDisconnect
	 */
	void OnInvokeDisconnect(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientNewEventTypeID
	 */
	void OnClientNew(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientRespawnEventTypeID
	 */
	void OnClientRespawn(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientReadyEventTypeID
	 */
	void OnClientReady(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientPrepareEventTypeID
	 */
	void OnClientPrepare(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientReconnectEventTypeID
	 */
	void OnClientReconnect(Class sender, CF_EventArgs args);

	/**
	 * @brief See: ClientDisconnectedEventTypeID
	 */
	void OnClientLogout(Class sender, CF_EventArgs args);

	/**
	 * @brief See: MissionServer::PlayerDisconnected - Fires when the player has disconnected from the server (OnClientReconnect won't fire)
	 */
	void OnClientDisconnect(Class sender, CF_EventArgs args);

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled(Class sender, CF_EventArgs args);
};
