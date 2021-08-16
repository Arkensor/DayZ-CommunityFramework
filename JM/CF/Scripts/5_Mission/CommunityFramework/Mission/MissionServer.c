modded class MissionServer
{
	protected bool m_bLoaded;

	void MissionServer()
	{
		m_bLoaded = false;

		GetRPCManager().AddRPC( "CF", "RecieveModList", this, SingeplayerExecutionType.Server );
	}

	void ~MissionServer()
	{
	}

	override void OnEvent( EventType eventTypeId, Param params ) 
	{
		super.OnEvent( eventTypeId, params );

		switch( eventTypeId )
		{
		case LogoutCancelEventTypeID:
			LogoutCancelEventParams logoutCancelParams;
			
			Class.CastTo( logoutCancelParams, params );

			CF_Module_WorldManager.OnClientLogoutCancelled( PlayerBase.Cast( logoutCancelParams.param1 ) );

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

		CF_Module_Manager.OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		CF_Module_Manager.OnMissionFinish();
	}

	void OnMissionLoaded()
	{
		CF_Module_Manager.OnMissionLoaded();
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect( player, identity );

		CF_Module_WorldManager.OnInvokeConnect( player, identity );
	}

	override void InvokeOnDisconnect( PlayerBase player )
	{
		super.InvokeOnDisconnect( player );

		CF_Module_WorldManager.OnInvokeDisconnect( player );
	}

	override void OnClientReadyEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReadyEvent( identity, player );

		CF_Module_WorldManager.OnClientReady( player, identity );
	}
	
	override void OnClientReconnectEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientReconnectEvent( identity, player );

		CF_Module_WorldManager.OnClientReconnect( player, identity );
	}
	
	override void OnClientRespawnEvent( PlayerIdentity identity, PlayerBase player )
	{
		super.OnClientRespawnEvent( identity, player );

		CF_Module_WorldManager.OnClientRespawn( player, identity );
	}
	
	override void OnClientDisconnectedEvent( PlayerIdentity identity, PlayerBase player, int logoutTime, bool authFailed )
	{
		super.OnClientDisconnectedEvent( identity, player, logoutTime, authFailed );

		CF_Module_WorldManager.OnClientLogout( player, identity, logoutTime, authFailed );
	}

	override void PlayerDisconnected( PlayerBase player, PlayerIdentity identity, string uid )
	{
		CF_Module_WorldManager.OnClientDisconnect( player, identity, uid );

		super.PlayerDisconnected( player, identity, uid );
	}

	override PlayerBase OnClientNewEvent( PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		PlayerBase player = super.OnClientNewEvent( identity, pos, ctx );

		CF_Module_WorldManager.OnClientNew( player, identity, pos, ctx );

		return player;
	} 

	override void OnClientPrepareEvent( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		CF_Module_WorldManager.OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout );
		
		super.OnClientPrepareEvent( identity, useDB, pos, yaw, preloadTimeout );
	}
}
