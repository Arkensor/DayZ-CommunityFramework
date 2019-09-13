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

	void OnMissionLoaded()
	{
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

		GetModuleManager().OnClientDisconnected( player, identity, logoutTime, authFailed );
	}

	override PlayerBase OnClientNewEvent( PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		if ( !GetModuleManager().OnClientNew( m_player, identity, pos, ctx ) )
		{
			return super.OnClientNewEvent( identity, pos, ctx );
		}

		return m_player;
	}

	override void OnClientPrepareEvent( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		if ( !GetModuleManager().OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout ) )
		{
			super.OnClientPrepareEvent( identity, useDB, pos, yaw, preloadTimeout );
		}
	}

	override void InvokeOnConnect( PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect( player, identity );
		
		//GetLogger().Send( identity );

		// GetRPCManager().SendRPC( "CF", "SendModList", new Param1< autoptr map< string, string > >( ModLoader.GetModMetaData() ), false, identity );
	}

}
