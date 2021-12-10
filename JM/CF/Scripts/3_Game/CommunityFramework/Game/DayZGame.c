modded class DayZGame
{
	void DayZGame()
	{
	}

	override void DeferredInit()
	{
		super.DeferredInit();

		GetRPCManager();
	}

	override void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
	{
		if ( rpc_type == NotificationSystemRPC.Create )
		{
			NotificationSystem.RPC_CreateNotification( sender, target, ctx );

			return;
		}

		if ( g_cf_ModuleManager )
		{
			g_cf_ModuleManager.OnRPC( sender, target, rpc_type, ctx );
		}

		super.OnRPC( sender, target, rpc_type, ctx );
	}
};