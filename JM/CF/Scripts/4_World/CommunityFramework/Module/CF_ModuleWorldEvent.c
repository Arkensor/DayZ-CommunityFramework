class CF_ModuleWorldEvent : CF_ModuleCoreEvent
{
	ref CF_ModuleWorld m_WorldModule;

	void CF_ModuleWorldEvent(CF_ModuleGame module = null)
	{
		if (module)
		{
			m_WorldModule = CF_ModuleWorld.Cast(module);
		}
	}

	void OnClientLogoutCancelled(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogoutCancelled(player, identity);
			}
		}
	}

	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeConnect(player, identity);
			}
		}
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeDisconnect(player);
			}
		}
	}

	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientNew(player, identity, pos, ctx);
			}
		}
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientRespawn(player, identity);
			}
		}
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReady(player, identity);
			}
		}
	}

	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
			}
		}
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReconnect(player, identity);
			}
		}
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogout(player, identity, logoutTime, authFailed);
			}
		}
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientDisconnect(player, identity, uid);
			}
		}
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			CF_ModuleWorld module = evt.m_WorldModule;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogoutCancelled(player);
			}
		}
	}
};
