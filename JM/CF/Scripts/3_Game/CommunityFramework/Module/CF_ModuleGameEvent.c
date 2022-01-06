class CF_ModuleGameEvent : CF_ModuleCoreEvent
{
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, Serializer ctx)
	{
		auto rpc = new CF_ModuleRPC();
		rpc.Sender = sender;
		rpc.Target = target;
		rpc.Type = rpc_type;

		auto evt = this.m_Next;
		while (evt)
		{
			auto module = CF_ModuleGame.Cast(evt.m_Value);

			if ((module.m_CF_GameFlag & CF_ModuleCoreManager.s_GameFlag) != 0 && (module.m_CF_RPC_Minimum <= rpc_type && rpc_type < module.m_CF_RPC_Maximum))
			{
				module.OnRPC(rpc, ctx);
				break;
			}

			evt = evt.m_Next;
		}
	}

	void OnUpdateInput(float dt)
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

class CF_ModuleRPC
{
	PlayerIdentity Sender;
	Object Target;
	int Type;
};
