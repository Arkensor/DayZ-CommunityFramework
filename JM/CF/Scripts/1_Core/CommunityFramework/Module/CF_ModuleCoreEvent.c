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

	void OnMissionStart()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionStart();
			}
			evt = evt.m_Next;
		}
	}

	void OnMissionFinish()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionFinish();
			}
			evt = evt.m_Next;
		}
	}

	void OnMissionLoaded()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMissionLoaded();
			}
			evt = evt.m_Next;
		}
	}

	void OnUpdate(float timeslice)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnUpdate(timeslice);
			}
			evt = evt.m_Next;
		}
	}

	void OnSettingsChanged()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnSettingsChanged();
			}
			evt = evt.m_Next;
		}
	}

	void OnPermissionsChanged()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnPermissionsChanged();
			}
			evt = evt.m_Next;
		}
	}

	void OnWorldCleanup()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnWorldCleanup();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionStart()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionStart();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionPlayerReady()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionPlayerReady();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionFail()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionFail();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionEnd()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPSessionEnd();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPConnectAbort()
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPConnectAbort();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPConnectionLost(int duration)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnMPConnectionLost(duration);
			}
			evt = evt.m_Next;
		}
	}

	void OnRespawn(int time)
	{
		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleCore module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.OnRespawn(time);
			}
			evt = evt.m_Next;
		}
	}
};
