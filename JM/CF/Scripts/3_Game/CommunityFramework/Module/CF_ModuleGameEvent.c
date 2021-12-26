class CF_ModuleGameEvent : CF_ModuleCoreEvent
{
	ref CF_ModuleGame m_GameModule;

	void CF_ModuleGameEvent(CF_ModuleGame module = null)
	{
		if (module)
		{
			m_GameModule = CF_ModuleGame.Cast(module);
		}
	}

	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, Serializer ctx)
	{
		CF_ModuleRPC rpc = new CF_ModuleRPC();
		rpc.Sender = sender;
		rpc.Target = target;
		rpc.Type = rpc_type;

		CF_ModuleCoreEvent evt = this.m_Next;
		while (evt)
		{
			CF_ModuleGame module = evt.m_Value;

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0 && rpc_type >= module.m_CF_RPC_Minimum && rpc_type < module.m_CF_RPC_Minimum)
			{
				module.OnRPC(rpc, ctx);
				break;
			}

			evt = evt.m_Next;
		}
	}
};

class CF_ModuleRPC
{
	PlayerIdentity Sender;
	Object Target;
	int Type;
};
