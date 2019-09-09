class CFLogger
{
	[NonSerialized()]
	static ref ScriptInvoker OnUpdate = new ScriptInvoker;

	[NonSerialized()]
	protected string m_FileName;

	bool EnableDebug;

	autoptr map< string, bool > Modes = new ref map< string, bool >;
	
	void CFLogger()
	{
		m_FileName = "$profile:CFLogger.json";

		Modes.Insert( "JM_CF_Mods", false );
		Modes.Insert( "JM_CF_RPC", false );
		Modes.Insert( "JM_CF_RPC_Client", false );
		Modes.Insert( "JM_CF_Credits", false );
		Modes.Insert( "JM_CF_KeyBindings", false );
	}

	void Copy( CFLogger cpy )
	{
		EnableDebug = cpy.EnableDebug;

		for ( int i = 0; i < cpy.Modes.Count(); i++)
		{
			string name = cpy.Modes.GetKey( i );

			if ( Modes.Contains( name ) )
			{
				Modes.Set( name, cpy.Modes.GetElement( i ) );
			}
		}

		Update();
	}

	bool IsOn( string type )
	{
		//if ( !EnableDebug )
		//	return false;
		//
		//bool on = false;
		//
		//if ( Modes.Find( type, on ) )
		//	return on;

		return false;
	}

	void Log( string text, string type )
	{
		//if ( !EnableDebug )
		//	return
		//
		//if ( IsOn( type ) )
		//	Print( type + ": " + text );
	}
	
	void Err( string text, string type, bool stackTrce = true )
	{
		if ( stackTrce )
		{
			Error( type + ": " + text );
		} else 
		{
			Print( type + ": " + text );
		}
	}
	
	static ref CFLogger Load()
	{
		ref CFLogger settings = new CFLogger();
		
		if ( GetGame().IsClient() )
			return settings;

		if ( FileExist( settings.m_FileName ) )
		{
			JsonFileLoader<CFLogger>.JsonLoadFile( settings.m_FileName, settings );
			
			OnUpdate.Invoke();
		} else {
			settings.Defaults();
			settings.Save();
		}

		return settings;
	}

	void Save()
	{
		JsonFileLoader<CFLogger>.JsonSaveFile( m_FileName, this );
	}
	
	void Defaults()
	{
	}
	
	void Send( PlayerIdentity sendTo )
	{
		GetRPCManager().SendRPC( "CF", "SetCFLogger", new Param1< ref CFLogger >( this ), false, sendTo );
	}
	
	/**
	\brief Saves and sends the debugging information
		@code
			GetLogger().JM_CF_Mods = true;
			GetLogger().Update();
		@endcode
	*/
	void Update()
	{
		if ( GetGame().IsServer() )
		{
			Send( NULL );
			Save();
		}

		OnUpdate.Invoke();
	}
}

static ref CFLogger g_CFLogger;

static ref CFLogger GetLogger()
{
	if ( !g_CFLogger )
	{
		g_CFLogger = CFLogger.Load();
	}

	return g_CFLogger;
}
