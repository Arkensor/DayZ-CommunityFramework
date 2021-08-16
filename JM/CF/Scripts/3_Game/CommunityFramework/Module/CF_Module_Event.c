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
			if (current == module) return;

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
			evt.m_Value.OnMissionStart();
			evt = evt.m_Next;
		}
	}

	void OnMissionFinish()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMissionFinish();
			evt = evt.m_Next;
		}
	}

	void OnMissionLoaded()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMissionLoaded();
			evt = evt.m_Next;
		}
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			CF_Module module = evt.m_Value;

			if (rpc_type >= module.m_CF_RPC_Minimum && rpc_type < module.m_CF_RPC_Minimum)
			{
				module.OnRPC(sender, target, rpc_type, ctx);
				break;
			}

			evt = evt.m_Next;
		}
	}
	
	void OnWorldCleanup()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnWorldCleanup();
			evt = evt.m_Next;
		}
	}

	void OnMPSessionStart()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPSessionStart();
			evt = evt.m_Next;
		}
	}

	void OnMPSessionPlayerReady()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPSessionPlayerReady();
			evt = evt.m_Next;
		}
	}

	void OnMPSessionFail()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPSessionFail();
			evt = evt.m_Next;
		}
	}

	void OnMPSessionEnd()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPSessionEnd();
			evt = evt.m_Next;
		}
	}

	void OnMPConnectAbort()
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPConnectAbort();
			evt = evt.m_Next;
		}
	}

	void OnMPConnectionLost(int duration)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnMPConnectionLost(duration);
			evt = evt.m_Next;
		}
	}

	void OnRespawn(int time)
	{
		CF_Module_Event evt = this.m_Next;
		while (evt)
		{
			evt.m_Value.OnRespawn(time);
			evt = evt.m_Next;
		}
	}
};
