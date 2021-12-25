class CF_Module_Event
{
	ref CF_Module m_Value;

	ref CF_Module_Event m_Next;

	void CF_Module_Event(CF_Module module = null)
	{
		m_Value = module;
	}

	void Add(CF_Module module)
	{
		CF_Module_Event newEvent = new CF_Module_Event(module);

		CF_Module_Event current = this;
		CF_Module_Event next = m_Next;
		while (current && next)
		{
			if (current == module)
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
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMissionStart();
			}
			evt = evt.m_Next;
		}
	}

	void OnMissionFinish()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMissionFinish();
			}
			evt = evt.m_Next;
		}
	}

	void OnMissionLoaded()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMissionLoaded();
			}
			evt = evt.m_Next;
		}
	}

	void OnUpdate(float timeslice)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnUpdate(timeslice);
			}
			evt = evt.m_Next;
		}
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0 && rpc_type >= module.m_CF_RPC_Minimum && rpc_type < module.m_CF_RPC_Minimum)
			{
				module.OnRPC(sender, target, rpc_type, ctx);
				break;
			}

			evt = evt.m_Next;
		}
	}

	void OnSettingsChanged()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnSettingsChanged();
			}
			evt = evt.m_Next;
		}
	}

	void OnPermissionsChanged()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnPermissionsChanged();
			}
			evt = evt.m_Next;
		}
	}

	void OnWorldCleanup()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnWorldCleanup();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionStart()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPSessionStart();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionPlayerReady()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPSessionPlayerReady();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionFail()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPSessionFail();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPSessionEnd()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPSessionEnd();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPConnectAbort()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPConnectAbort();
			}
			evt = evt.m_Next;
		}
	}

	void OnMPConnectionLost(int duration)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnMPConnectionLost(duration);
			}
			evt = evt.m_Next;
		}
	}

	void OnRespawn(int time)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;
			if ((module.m_CF_GameFlag & CF_Module_Manager.s_GameFlag) != 0)
			{
				module.OnRespawn(time);
			}
			evt = evt.m_Next;
		}
	}
};
