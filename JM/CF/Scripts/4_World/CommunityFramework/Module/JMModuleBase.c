class JMModuleBase : CF_WorldModule
{
	/**
	 * Any module that inherits from 'JMModuleBase' probably expects all events to be enabled
	 */
	override void OnInit()
	{
		super.OnInit();

		EnableUpdate();
		EnableMissionStart();
		EnableMissionFinish();
		EnableMissionLoaded();
		EnableRPC();
		EnableWorldCleanup();
		EnableMPSessionStart();
		EnableMPSessionPlayerReady();
		EnableMPSessionFail();
		EnableMPSessionEnd();
		EnableMPConnectAbort();
		EnableMPConnectionLost();
		EnableRespawn();
		EnableInvokeConnect();
		EnableInvokeDisconnect();
		EnableClientNew();
		EnableClientRespawn();
		EnableClientReady();
		EnableClientPrepare();
		EnableClientLogoutReconnect();
		EnableClientLogout();
		EnableClientDisconnect();
		EnableClientLogoutCancelled();
	}

	void RegisterKeyMouseBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterKeyMouseBinding", "Bind");
	}

	void RegisterBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterBinding", "Bind");
	}
};
