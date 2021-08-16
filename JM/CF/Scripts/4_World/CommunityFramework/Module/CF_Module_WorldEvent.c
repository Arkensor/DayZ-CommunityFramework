class CF_Module_WorldEvent : CF_Module_Event
{
	ref CF_WorldModule m_WorldModule;

	void CF_Module_WorldEvent(CF_Module module = null)
	{
		if (module)
		{
			m_WorldModule = CF_WorldModule.Cast(module);
		}
	}

	void OnClientLogoutCancelled(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientLogoutCancelled(player, identity);
		}
	}

	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnInvokeConnect(player, identity);
		}
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnInvokeDisconnect(player);
		}
	}

	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientNew(player, identity, pos, ctx);
		}
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientRespawn(player, identity);
		}
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientReady(player, identity);
		}
	}

	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
		}
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientReconnect(player, identity);
		}
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientLogout(player, identity, logoutTime, authFailed);
		}
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientDisconnect(player, identity, uid);
		}
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			evt.m_WorldModule.OnClientLogoutCancelled(player);
		}
	}
};
