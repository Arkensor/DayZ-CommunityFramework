modded class DayZGame
{
	ref CF_EventRPCArgs m_CF_EventRPCArgs = new CF_EventRPCArgs();

	void DayZGame()
	{
		CF_ModuleGameManager.UpdateGameFlag(this);
	}

	override void DeferredInit()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif

		super.DeferredInit();

		GetRPCManager();
	}

	override void OnUpdate(bool doSim, float timeslice)
	{
		super.OnUpdate(doSim, timeslice);

		if (!GetGame().IsDedicatedServer())
		{
			foreach (auto input : CF_InputBindings.s_All)
			{
				input.Update(timeslice);
			}
		}
	}

	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this).Add(sender).Add(target).Add(rpc_type).Add(ctx);
#endif

		if (rpc_type == RPCManager.FRAMEWORK_RPC_ID)
		{
			GetRPCManager().OnRPC(sender, target, rpc_type, ctx);

			return;
		}

		if (rpc_type == NotificationSystemRPC.Create)
		{
			NotificationSystem.RPC_CreateNotification(sender, target, ctx);

			return;
		}

		if (rpc_type == CF_ModuleGame.NETWORKED_VARIABLES_RPC_ID)
		{
			// Only allow this RPC to be executed on the client, don't want to allow the client to edit server variables
			if (GetGame().IsServer())
			{
				return;
			}

			string moduleName;
			if (!ctx.Read(moduleName))
			{
				return;
			}

			// Check to see if the module can be found
			CF_ModuleGame module;
			if (!Class.CastTo(module, CF_ModuleCoreManager.Get(moduleName)))
			{
				return;
			}

			module.m_CF_NetworkedVariables.Read(ctx);

			module.OnVariablesSynchronized(this, CF_EventArgs.Empty);

			return;
		}

		m_CF_EventRPCArgs.Sender = sender;
		m_CF_EventRPCArgs.Target = target;
		m_CF_EventRPCArgs.ID = rpc_type;
		m_CF_EventRPCArgs.Context = ctx;

		if (CF_ModuleGameManager.OnRPC(this, m_CF_EventRPCArgs))
		{
			return;
		}

		super.OnRPC(sender, target, rpc_type, ctx);
	}

	override void OnEvent(EventType eventTypeId, Param params)
	{
		super.OnEvent(eventTypeId, params);

		switch (eventTypeId)
		{
		case MPSessionStartEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionStart(this, CF_EventArgs.Empty);

			break;
		}
		case MPSessionEndEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionEnd(this, CF_EventArgs.Empty);

			break;
		}
		case MPSessionFailEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionFail(this, CF_EventArgs.Empty);

			break;
		}
		case MPSessionPlayerReadyEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionPlayerReady(this, CF_EventArgs.Empty);

			break;
		}
		case MPConnectionLostEventTypeID:
		{
			MPConnectionLostEventParams conLost_params;
			if (Class.CastTo(conLost_params, params))
			{
				CF_ModuleCoreManager.OnMPConnectionLost(this, new CF_EventTimeArgs(conLost_params.param1));
			}
			break;
		}
		case WorldCleaupEventTypeID:
		{
			CF_ModuleCoreManager.OnWorldCleanup(this, CF_EventArgs.Empty);

			break;
		}
		case ChatMessageEventTypeID:
		{
			ChatMessageEventParams chat_params;
			if (Class.CastTo(chat_params, params))
			{
				CF_ModuleCoreManager.OnChat(this, new CF_EventChatArgs(chat_params.param1, chat_params.param2, chat_params.param3, chat_params.param4));
			}

			break;
		}
		case LoginTimeEventTypeID:
		{
			LoginTimeEventParams loginTimeParams;
			if (Class.CastTo(loginTimeParams, params))
			{
				CF_ModuleCoreManager.OnLoginTime(this, new CF_EventTimeArgs(loginTimeParams.param1));
			}
			break;
		}
		case RespawnEventTypeID:
		{
			RespawnEventParams respawnParams;
			if (Class.CastTo(respawnParams, params))
			{
				CF_ModuleCoreManager.OnRespawn(this, new CF_EventTimeArgs(respawnParams.param1));
			}
			break;
		}
		case LogoutEventTypeID:
		{
			LogoutEventParams logoutParams;
			if (Class.CastTo(logoutParams, params))
			{
				CF_ModuleCoreManager.OnLogout(this, new CF_EventTimeArgs(logoutParams.param1));
			}
			break;
		}
		case LoginStatusEventTypeID:
		{
			LoginStatusEventParams loginStatusParams;
			if (Class.CastTo(loginStatusParams, params))
			{
				CF_ModuleCoreManager.OnLoginStatus(this, new CF_EventLoginArgs(loginStatusParams.param1, loginStatusParams.param2));
			}
			break;
		}
		case ConnectingAbortEventTypeID:
		{
			CF_ModuleCoreManager.OnMPConnectAbort(this, CF_EventArgs.Empty);
			break;
		}
		}
	}

	/**
	 * @brief An overrideable function that determines if the UI input of the player is being blocked by an editbox widget.
	 */
	bool CF_UIInputBlocked()
	{
		if (GetGame().IsDedicatedServer())
		{
			return false;
		}

		Widget focusedWidget = GetFocus();
		if (!focusedWidget)
		{
			return false;
		}

		return focusedWidget.ClassName().Contains("EditBoxWidget");
	}
};
