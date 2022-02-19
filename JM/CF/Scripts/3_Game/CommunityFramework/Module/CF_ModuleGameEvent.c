class CF_ModuleGameEvent : CF_ModuleCoreEvent
{
	bool OnRPC(Class sender, CF_EventArgs args)
	{
		CF_EventRPCArgs rpc;
		if (!Class.CastTo(rpc, args))
		{
			return false;
		}

		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleGame.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0 && (module.m_CF_RPC_Minimum <= rpc.ID && rpc.ID < module.m_CF_RPC_Maximum))
			{
				module.OnRPC(sender, rpc);
				return true;
			}

			evt = evt.m_Next;
		}

		return false;
	}
};
