class CF_ModuleCoreEvent
{
	ref CF_ModuleCore m_Value;

	ref CF_ModuleCoreEvent m_Next;

	void CF_ModuleCoreEvent(CF_ModuleCore module = null)
	{
		m_Value = module;
	}

	void Add(CF_ModuleCore module)
	{
		CF_ModuleCoreEvent newEvent = new CF_ModuleCoreEvent(module);

		CF_ModuleCoreEvent current = this;
		CF_ModuleCoreEvent next = m_Next;
		while (current && next)
		{
			if (current.m_Value == module || next.m_Value == module)
			{
				return;
			}

			current = next;
			next = next.m_Next;
		}

		current.m_Next = newEvent;
	}

	void OnMissionStart(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionStart(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMissionFinish(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionFinish(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMissionLoaded(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionLoaded(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnUpdate(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnUpdate(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnSettingsChanged(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnSettingsChanged(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnPermissionsChanged(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnPermissionsChanged(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnWorldCleanup(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnWorldCleanup(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPSessionStart(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionStart(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPSessionPlayerReady(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionPlayerReady(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPSessionFail(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionFail(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPSessionEnd(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionEnd(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPConnectAbort(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPConnectAbort(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnMPConnectionLost(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPConnectionLost(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnRespawn(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnRespawn(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnLoginTime(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnLoginTime(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnLoginStatus(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnLoginStatus(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnLogout(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnLogout(sender, args);
			}

			evt = evt.m_Next;
		}
	}

	void OnChat(Class sender, CF_EventArgs args)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnChat(sender, args);
			}

			evt = evt.m_Next;
		}
	}
};
