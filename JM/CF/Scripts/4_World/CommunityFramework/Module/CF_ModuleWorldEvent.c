class CF_ModuleWorldEvent : CF_ModuleCoreEvent
{
	void OnInvokeConnect(PlayerBase player, PlayerIdentity identity)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeConnect(player, identity);
			}

			evt = evt.m_Next;
		}
	}

	void OnInvokeDisconnect(PlayerBase player)
	{
		CF_ModuleWorldEvent evt = this;
		while (Class.CastTo(evt, evt.m_Next))
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeDisconnect(player);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientNew(inout PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientNew(player, identity, pos, ctx);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientRespawn(PlayerBase player, PlayerIdentity identity)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientRespawn(player, identity);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientReady(PlayerBase player, PlayerIdentity identity)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReady(player, identity);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientPrepare(PlayerIdentity identity, inout bool useDB, inout vector pos, inout float yaw, inout int preloadTimeout)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientPrepare(identity, useDB, pos, yaw, preloadTimeout);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientReconnect(PlayerBase player, PlayerIdentity identity)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReconnect(player, identity);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientLogout(PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogout(player, identity, logoutTime, authFailed);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientDisconnect(PlayerBase player, PlayerIdentity identity, string uid)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientDisconnect(player, identity, uid);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientLogoutCancelled(PlayerBase player)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogoutCancelled(player);
			}

			evt = evt.m_Next;
		}
	}
};
