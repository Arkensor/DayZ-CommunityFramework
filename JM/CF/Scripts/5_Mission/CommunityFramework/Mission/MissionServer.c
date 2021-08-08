modded class MissionServer
{
	protected bool m_bLoaded;

	void MissionServer()
	{
		m_bLoaded = false;

		bool enabled = GetGame().ServerConfigGetInt("cfDebugUI") != 0;
		CF_Debug.SetAllowed(enabled);
	}

	void ~MissionServer()
	{
		CF_Debug.SetAllowed(false);
	}

	override void OnEvent( EventType eventTypeId, Param params ) 
	{
		super.OnEvent( eventTypeId, params );

		switch( eventTypeId )
		{
		case ClientPrepareEventTypeID:
			ClientPrepareEventParams clientPrepareParams;
			Class.CastTo(clientPrepareParams, params);
			CF_SendDebugUIState(clientPrepareParams.param1);
			break;
		case ClientNewEventTypeID:
			ClientNewEventParams newParams;
			Class.CastTo(newParams, params);
			CF_SendDebugUIState(newParams.param1);
			break;
		case ClientReadyEventTypeID:
			ClientReadyEventParams readyParams;
			Class.CastTo(readyParams, params);
			CF_SendDebugUIState(readyParams.param1);
			break;
		case ClientReadyEventTypeID:
			ClientReconnectEventParams reconnectParams;
			Class.CastTo(reconnectParams, params);
			CF_SendDebugUIState(reconnectParams.param1);
			break;
		case LogoutCancelEventTypeID:
			LogoutCancelEventParams logoutCancelParams;
			
			Class.CastTo( logoutCancelParams, params );

			GetModuleManager().OnClientLogoutCancelled( PlayerBase.Cast( logoutCancelParams.param1 ) );

			break;
		}
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetModuleManager().OnSettingsUpdated();
		GetModuleManager().OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetModuleManager().OnMissionFinish();
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		GetModuleManager().OnMissionLoaded();
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );

		GetModuleManager().OnUpdate( timeslice );
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect( player, identity );

		GetModuleManager().OnInvokeConnect( player, identity );
	}

	override void InvokeOnDisconnect( PlayerBase player )
	{
		super.InvokeOnDisconnect( player );

		GetModuleManager().OnInvokeDisconnect( player );
	}

	override void OnClientReadyEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReadyEvent( identity, player );

		GetModuleManager().OnClientReady( player, identity );
	}
	
	override void OnClientReconnectEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReconnectEvent( identity, player );

		GetModuleManager().OnClientReconnect( player, identity );
	}
	
	override void OnClientRespawnEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientRespawnEvent( identity, player );

		GetModuleManager().OnClientRespawn( player, identity );
	}
	
	override void OnClientDisconnectedEvent( PlayerIdentity identity, PlayerBase player, int logoutTime, bool authFailed )
	{
		super.OnClientDisconnectedEvent( identity, player, logoutTime, authFailed );

		GetModuleManager().OnClientLogout( player, identity, logoutTime, authFailed );
	}

	override void PlayerDisconnected( PlayerBase player, PlayerIdentity identity, string uid )
	{
		GetModuleManager().OnClientDisconnect( player, identity, uid );

		super.PlayerDisconnected( player, identity, uid );
	}

	override PlayerBase OnClientNewEvent( PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		PlayerBase player = super.OnClientNewEvent( identity, pos, ctx );

		GetModuleManager().OnClientNew( player, identity, pos, ctx );

		return player;
	} 

	override void OnClientPrepareEvent( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		GetModuleManager().OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout );
		
		super.OnClientPrepareEvent( identity, useDB, pos, yaw, preloadTimeout );
	}
}
