class CF_ModuleGameManager
{
	static ref CF_ModuleGameEvent s_RPC = new CF_ModuleGameEvent();
	static ref CF_ModuleGameEvent s_UpdateInput = new CF_ModuleGameEvent();

	static void UpdateGameFlag(CGame game = null)
	{
		if (game == null)
		{
			game = GetGame();
		}

		CF_ModuleCoreManager.s_GameFlag = 0xFF;
		if (game.IsMultiplayer())
		{
			CF_ModuleCoreManager.s_GameFlag = 0x0F;
			if (game.IsServer())
			{
				CF_ModuleCoreManager.s_GameFlag = 0xF0;
			}
		}
	}

	static void OnRPC(PlayerIdentity sender, Object target, int rpc_type, Serializer ctx)
	{
		s_RPC.OnRPC(sender, target, rpc_type, ctx);
	}

	static void OnUpdate(float dt)
	{
		UpdateGameFlag();

		CF_ModuleCoreManager.s_Update.OnUpdate(dt);

		if (!CF_ModuleCore.s_PreventInput)
		{
			s_UpdateInput.OnUpdateInput(dt);
		}
	}
};
