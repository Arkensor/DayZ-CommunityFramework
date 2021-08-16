class CF_WorldModule : CF_Module
{
	void EnableInvokeConnect()
	{
		CF_Module_WorldManager.s_InvokeConnect.Add(this);
	}

	void EnableInvokeDisconnect()
	{
		CF_Module_WorldManager.s_InvokeDisconnect.Add(this);
	}

	void EnableClientNew()
	{
		CF_Module_WorldManager.s_ClientNew.Add(this);
	}

	void EnableClientRespawn()
	{
		CF_Module_WorldManager.s_ClientRespawn.Add(this);
	}

	void EnableClientReady()
	{
		CF_Module_WorldManager.s_ClientReady.Add(this);
	}

	void EnableClientPrepare()
	{
		CF_Module_WorldManager.s_ClientPrepare.Add(this);
	}

	void EnableClientLogoutReconnect()
	{
		CF_Module_WorldManager.s_ClientReconnect.Add(this);
	}

	void EnableClientLogout()
	{
		CF_Module_WorldManager.s_ClientLogout.Add(this);
	}

	void EnableClientDisconnect()
	{
		CF_Module_WorldManager.s_ClientDisconnect.Add(this);
	}

	void EnableClientLogoutCancelled()
	{
		CF_Module_WorldManager.s_ClientLogoutCancelled.Add(this);
	}

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled(PlayerBase player, PlayerIdentity identity);

	/**
	 * @brief See: MissionServer::InvokeOnConnect
	 */
	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity);

	/**
	 * @brief See: MissionServer::InvokeOnDisconnect
	 */
	void OnInvokeDisconnect(PlayerBase player);

	/**
	 * @brief See: ClientNewEventTypeID
	 */
	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx);

	/**
	 * @brief See: ClientRespawnEventTypeID
	 */
	void OnClientRespawn(PlayerBase player, PlayerIdentity identity);

	/**
	 * @brief See: ClientReadyEventTypeID
	 */
	void OnClientReady(PlayerBase player, PlayerIdentity identity);

	/**
	 * @brief See: ClientPrepareEventTypeID
	 */
	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout);

	/**
	 * @brief See: ClientReconnectEventTypeID
	 */
	void OnClientReconnect(PlayerBase player, PlayerIdentity identity);

	/**
	 * @brief See: ClientDisconnectedEventTypeID
	 */
	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed);

	/**
	 * @brief See: MissionServer::PlayerDisconnected - Fires when the player has disconnected from the server (OnClientReconnect won't fire)
	 */
	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid);

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled(PlayerBase player);
};
