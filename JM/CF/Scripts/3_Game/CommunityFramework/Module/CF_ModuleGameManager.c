class CF_ModuleGameManager
{
	static ref CF_ModuleGameEvent s_RPC = new CF_ModuleGameEvent();
	static ref CF_ModuleGameEvent s_UpdateInput = new CF_ModuleGameEvent();

	/**
	 * @brief Updates the flag for event calling. So server side modules don't get the event called on client and same for client side on server.
	 * 
	 * @param game Passes in the CGame/DayZGame instance. If none provided, automatically obtains from global 'g_Game' variable
	 */
	static void UpdateGameFlag(CGame game = null)
	{
		if (game == null)
		{
			game = g_Game;
		}

		// 0xFF = Single Player
		// 0x0F = Client
		// 0xF0 = Dedicated Server
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
		if (!GetGame().IsDedicatedServer() && !GetDayZGame().CF_UIInputBlocked())
		{
			s_UpdateInput.UpdateGameEventInputs(CF_EventUpdateArgs.Cast(args).DeltaTime);
		}
	}
};
