modded class DayZGame
{
	void DayZGame()
	{
		CF_ModuleGameManager.UpdateGameFlag(this);
	}

	override void DeferredInit()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "DeferredInit");
#endif

		super.DeferredInit();

		GetRPCManager();
	}

	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this, "OnRPC").Add(sender).Add(target).Add(rpc_type).Add(ctx);
#endif

		if (rpc_type == NotificationSystemRPC.Create)
		{
			NotificationSystem.RPC_CreateNotification(sender, target, ctx);

			return;
		}

		auto rpcArgs = new CF_EventRPCArgs();
		rpcArgs.Sender = sender;
		rpcArgs.Target = target;
		rpcArgs.ID = rpc_type;
		rpcArgs.Context = ctx;

		CF_ModuleGameManager.OnRPC(this, rpcArgs);

		super.OnRPC(sender, target, rpc_type, ctx);
	}

	override void OnEvent(EventType eventTypeId, Param params)
	{
		super.OnEvent(eventTypeId, params);

		switch (eventTypeId)
		{
		case MPSessionStartEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionStart(this, new CF_EventArgs);

			break;
		}
		case MPSessionEndEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionEnd(this, new CF_EventArgs);

			break;
		}
		case MPSessionFailEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionFail(this, new CF_EventArgs);

			break;
		}
		case MPSessionPlayerReadyEventTypeID:
		{
			CF_ModuleCoreManager.OnMPSessionPlayerReady(this, new CF_EventArgs);

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
			CF_ModuleCoreManager.OnWorldCleanup(this, new CF_EventArgs);

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
				CF_ModuleCoreManager.OnMPConnectionLost(this, new CF_EventTimeArgs(respawnParams.param1));
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
			CF_ModuleCoreManager.OnMPConnectAbort(this, new CF_EventArgs);
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