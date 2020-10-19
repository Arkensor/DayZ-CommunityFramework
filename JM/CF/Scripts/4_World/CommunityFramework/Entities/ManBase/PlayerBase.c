modded class PlayerBase
{
	private JMPlayerInstance m_AuthenticatedPlayer;

	override void Init()
	{
		super.Init();
		
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetAuthenticatedPlayer, 2000, false );
	}
	
	JMPlayerInstance GetAuthenticatedPlayer()
	{
		if ( m_AuthenticatedPlayer )
			return m_AuthenticatedPlayer;

		if ( !GetIdentity() ) // Could be AI
			return NULL;

		if ( !m_AuthenticatedPlayer )
		{
			if ( IsMissionOffline() )
			{
				m_AuthenticatedPlayer = GetPermissionsManager().GetClientPlayer();
			} else
			{
				m_AuthenticatedPlayer = GetPermissionsManager().GetPlayer( GetIdentity().GetId() );
			}
		}

		if ( Assert_Null( m_AuthenticatedPlayer ) )
			return NULL;
		
		m_AuthenticatedPlayer.PlayerObject = this;
		return m_AuthenticatedPlayer;
	}
	
	override string FormatSteamWebhook()
	{
		if ( Assert_Null( GetAuthenticatedPlayer(), "Player has no identity or improperly programmed AI mod" ) )
		{
			return super.FormatSteamWebhook() + " (WARNING)";
		}

		return GetAuthenticatedPlayer().FormatSteamWebhook();
	}
};