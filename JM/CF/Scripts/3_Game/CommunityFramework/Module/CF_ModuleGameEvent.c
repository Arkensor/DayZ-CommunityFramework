class CF_ModuleGameEvent : CF_ModuleCoreEvent
{
	void OnRPC(Class sender, CF_EventArgs args)
	{
		CF_EventRPCArgs rpc;
		if (!Class.CastTo(rpc, args))
		{
			return;
		}

		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleGame.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0 && (module.m_CF_RPC_Minimum <= rpc.ID && rpc.ID < module.m_CF_RPC_Maximum))
			{
				module.OnRPC(sender, rpc);
				break;
			}

			evt = evt.m_Next;
		}
	}

	void UpdateGameEventInputs(float dt)
	{
		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleGame.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0)
			{
				module.m_CF_Bindings.Update(dt);
			}

			evt = evt.m_Next;
		}
	}
};
