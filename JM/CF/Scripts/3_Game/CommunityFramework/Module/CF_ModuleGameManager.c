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

	static void OnRPC(Class sender, CF_EventArgs args)
	{
		s_RPC.OnRPC(sender, args);
	}

	static void OnUpdate(Class sender, CF_EventArgs args)
	{
		UpdateGameFlag();

		CF_ModuleCoreManager.s_Update.OnUpdate(sender, args);

		// Don't allow input if we are editing an edit box or we are the server
		if (!GetGame().IsDedicatedServer() && !GetDayZGame().CF_IsInputInEditbox())
		{
			s_UpdateInput.UpdateGameEventInputs(CF_EventUpdateArgs.Cast(args).DeltaTime);
		}
	}
};
