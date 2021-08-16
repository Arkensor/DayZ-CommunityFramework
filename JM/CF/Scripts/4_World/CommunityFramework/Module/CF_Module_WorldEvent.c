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
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientLogoutCancelled(player, identity);
		}
	}

	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnInvokeConnect(player, identity);
		}
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnInvokeDisconnect(player);
		}
	}

	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientNew(player, identity, pos, ctx);
		}
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientRespawn(player, identity);
		}
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientReady(player, identity);
		}
	}

	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
		}
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientReconnect(player, identity);
		}
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientLogout(player, identity, logoutTime, authFailed);
		}
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientDisconnect(player, identity, uid);
		}
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		CF_Module_WorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_WorldModule module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0) module.OnClientLogoutCancelled(player);
		}
	}
};
