modded class DayZGame
{
	void DayZGame()
	{
		Print( "CommunityFramework Loaded" );

		#ifdef CF_THIS_LOADS
		Print("Wowee this worked");
		#endif

		#ifdef CF_DEFINE_TEST
		int i = 0;
		while ( i < 100 )
		{
			i++;
			Print( i );
			Print( "THIS WORKS!" );
		}
		#else
		Print( "FAILED WORKS!" );
		#endif

		CFCrasher.Perform();
	}

	override void DeferredInit()
	{
		super.DeferredInit();

		GetRPCManager();
		//GetLogger();
	}

	override void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
	{
		if ( rpc_type == NotificationSystemRPC.Create )
		{
			NotificationSystem.RPC_CreateNotification( sender, target, ctx );

			return;
		}
	
		g_cf_ModuleManager.OnRPC( sender, target, rpc_type, ctx );

		super.OnRPC( sender, target, rpc_type, ctx );
	}
}