class CF_ModuleWorldEvent : CF_ModuleCoreEvent
{
	void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeConnect(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnInvokeDisconnect(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnInvokeDisconnect(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientNew(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientNew(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientRespawn(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientRespawn(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientReady(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReady(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientPrepare(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientPrepare(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientReconnect(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientReconnect(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientLogout(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogout(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientDisconnect(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientDisconnect(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnClientLogoutCancelled(Class sender, CF_EventArgs args)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleWorld.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnClientLogoutCancelled(sender, args);
			}

			evt = evt.m_Next;
		}
	}
};
