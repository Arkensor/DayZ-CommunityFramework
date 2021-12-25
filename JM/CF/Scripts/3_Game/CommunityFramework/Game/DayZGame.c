modded class DayZGame
{
	void DayZGame()
	{
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

		CF_Module_Manager.OnRPC(sender, target, rpc_type, ctx);

		super.OnRPC(sender, target, rpc_type, ctx);
	}
};