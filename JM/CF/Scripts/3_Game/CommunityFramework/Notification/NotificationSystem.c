enum NotificationSystemRPC
{
	INVALID = 9000,
	Create,
	COUNT
};

modded class NotificationSystem
{
	void NotificationSystem()
	{
		g_Game.Event_OnRPC.Insert( OnRPC );
	}

	void ~NotificationSystem()
	{
		g_Game.Event_OnRPC.Remove( OnRPC );
	}

	void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx )
	{
		switch ( rpc_type )
		{
		case NotificationSystemRPC.Create:
			RPC_CreateNotification( ctx, sender, target );
			break;
		}
	}

	static void Create( ref StringLocaliser title, ref StringLocaliser text, string icon, int color, float time = 3, PlayerIdentity sendTo = NULL )
	{
		Print("NotificationSystem::Create - Start");
		
		if ( !m_Instance )
			return;
		
		m_Instance.CreateNotification( title, text, icon, color, time, sendTo );
		
		Print("NotificationSystem::Create - End");
	}

	// ------------------------------------------------------------
	void CreateNotification( ref StringLocaliser title, ref StringLocaliser text, string icon, int color, float time = 3, PlayerIdentity sendTo = NULL )
	{
		Print("NotificationSystem::CreateNotification - Start");
		
		if ( IsMissionHost() )
		{
			ScriptRPC rpc = new ScriptRPC();
			rpc.Write( title );
			rpc.Write( text );
			rpc.Write( icon );
			rpc.Write( color );
			rpc.Write( time );
			rpc.Send( NULL, NotificationSystemRPC.Create, true, sendTo );
		} 
		else
		{
			Exec_CreateNotification( title, text, icon, color, time );
		}
		
		Print("NotificationSystem::CreateNotification - End");
	}

	private void Exec_CreateNotification( ref StringLocaliser title, ref StringLocaliser text, string icon, int color, float time )
	{
		Print("NotificationSystem::CreateNotification - Start");
		
		ref NotificationRuntimeData data = new NotificationRuntimeData( time, new NotificationData( icon, title.Format() ), text.Format() );
		data.SetColor( color );

		AddNotif( data );
		
		Print("NotificationSystem::Exec_CreateNotification - End");
	}

	private void RPC_CreateNotification( ref ParamsReadContext ctx, PlayerIdentity senderRPC, Object target )
	{
		Print("NotificationSystem::RPC_CreateNotification - Start");
		
		ref StringLocaliser title = new StringLocaliser( "" );
		if ( !ctx.Read( title ) )
			return;

		ref StringLocaliser text = new StringLocaliser( "" );
		if ( !ctx.Read( text ) )
			return;

		string icon;
		if ( !ctx.Read( icon ) )
			return;

		int color;
		if ( !ctx.Read( color ) )
			return;

		float time;
		if ( !ctx.Read( time ) )
			return;

		Exec_CreateNotification( title, text, icon, color, time );
		
		Print("NotificationSystem::RPC_CreateNotification - End");
	}

	/*
	override this for the custom expansion notifications
	*/
	protected void AddNotif( ref NotificationRuntimeData data )
	{
		Print("NotificationSystem::AddNotif - Start");
		
		if ( m_TimeArray.Count() < MAX_NOTIFICATIONS )
		{
			float time = GetGame().GetTickTime() + data.GetTime();
			data.SetTime( time + NOTIFICATION_FADE_TIME );

			m_TimeArray.Insert( data );
			m_OnNotificationAdded.Invoke( data );
		} 
		else
		{
			m_DeferredArray.Insert( data );
		}
		
		Print("NotificationSystem::AddNotif - End");
	}

	override NotificationData GetNotificationData( NotificationType type )
	{		
		if ( m_DataArray.Contains(type) )
		{
			return m_DataArray.Get( type );
		}
		
		return null;
	}

	override static void AddNotification( NotificationType type, float show_time, string detail_text = "" )
	{
		ref NotificationRuntimeData data = new NotificationRuntimeData( show_time, m_Instance.GetNotificationData( type ), detail_text );

		m_Instance.AddNotif( data );
	}

	override static void AddNotificationExtended( float show_time, string title_text, string detail_text = "", string icon = "" )
	{
		ref NotificationData temp_data = new NotificationData( icon, title_text );
		ref NotificationRuntimeData data = new NotificationRuntimeData( show_time, temp_data, detail_text );

		m_Instance.AddNotif( data );
	}

	override static void SendNotificationToPlayerIdentityExtended( PlayerIdentity player, float show_time, string title_text, string detail_text = "", string icon = "" )
	{
		StringLocaliser oTitle = new StringLocaliser( title_text );
		StringLocaliser oText = new StringLocaliser( detail_text );

		oTitle.SetTranslates( false );
		oText.SetTranslates( false );

		Create( oTitle, oText, icon, ARGB( 255, 221, 38, 38 ), show_time, player );
	}

	override static void SendNotificationToPlayerIdentity( PlayerIdentity player, NotificationType type, float show_time, string detail_text = "" )
	{
		NotificationData sData = m_Instance.GetNotificationData( type );

		if ( !sData )
			return;

		StringLocaliser oTitle = new StringLocaliser( sData.m_TitleText );
		StringLocaliser oText;

		if ( detail_text != "" )
		{
			oText = new StringLocaliser( detail_text );
		} else
		{
			oText = new StringLocaliser( sData.m_DescriptionText );
		}

		oTitle.SetTranslates( false );
		oText.SetTranslates( false );

		Create( oTitle, oText, sData.m_Icon, ARGB( 255, 221, 38, 38 ), show_time, player );
	}
}