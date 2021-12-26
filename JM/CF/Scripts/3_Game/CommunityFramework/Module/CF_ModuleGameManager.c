class CF_ModuleGameManager
{
	static ref CF_ModuleGameEvent s_RPC = new CF_ModuleGameEvent();

	static void OnRPC(PlayerIdentity sender, Object target, int rpc_type, Serializer ctx)
	{
		s_RPC.OnRPC(sender, target, rpc_type, ctx);
	}

	static void _Update(float timeslice)
	{
		CF_ModuleCoreManager.s_GameFlag = 0xFF;
		if (GetGame().IsMultiplayer())
		{
			CF_ModuleCoreManager.s_GameFlag = 0x0F;
			if (GetGame().IsServer())
			{
				CF_ModuleCoreManager.s_GameFlag = 0xF0;
			}
		}

		CF_ModuleCoreManager.s_Update.OnUpdate(timeslice);
	}
};
