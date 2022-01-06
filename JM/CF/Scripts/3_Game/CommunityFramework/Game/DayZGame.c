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

	override void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this, "OnRPC").Add(sender).Add(target).Add(rpc_type).Add(ctx);
		#endif

		if ( rpc_type == NotificationSystemRPC.Create )
		{
			NotificationSystem.RPC_CreateNotification( sender, target, ctx );

			return;
		}

		auto rpcArgs = new CF_EventRPCArgs();
		rpcArgs.Sender = sender;
		rpcArgs.Target = target;
		rpcArgs.ID = rpc_type;
		rpcArgs.Context = ctx;
		
		CF_ModuleGameManager.OnRPC(this, rpcArgs);

		super.OnRPC( sender, target, rpc_type, ctx );
	}

	bool CF_IsInputInEditbox()
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