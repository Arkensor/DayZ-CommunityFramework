class Debugging
{
	[NonSerialized()]
	static ref ScriptInvoker OnUpdate = new ScriptInvoker;

	[NonSerialized()]
	string m_FileName;

	bool EnableDebug;

	autoptr map< string, bool > Modes = new ref map< string, bool >;
	
	protected void Debugging()
	{
		m_FileName = "$profile:Debugging.json";

		Modes.Insert( "JM_CF_Mods", false );
		Modes.Insert( "JM_CF_RPC", false );
		Modes.Insert( "JM_CF_Credits", false );
		Modes.Insert( "JM_CF_KeyBindings", false );
	}

	void Copy( ref Debugging cpy )
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

	void Log( string text, string type )
	{
		if ( !EnableDebug )
			return

		bool shouldPrintOut = false;
		
		bool found = Modes.Find( type, shouldPrintOut );
		
		if ( found && shouldPrintOut )
			Print( "" + text );
	}
	
	void Err( string text, string type )
	{
		//if ( !EnableDebug )
		//	return

		//bool shouldPrintOut = false;
		
		//bool found = Modes.Find( type, shouldPrintOut );
		
		//if ( found && shouldPrintOut )
			Error( "" + text );
	}
	
	static ref Debugging Load()
	{
		ref Debugging settings = new Debugging();
		
		if ( GetGame().IsClient() )
			return settings;

		if ( FileExist( settings.m_FileName ) )
		{
			JsonFileLoader<Debugging>.JsonLoadFile( settings.m_FileName, settings );
		} else {
			settings.Defaults();
			settings.Save();
		}

		return settings;
	}

	void Save()
	{
		JsonFileLoader<Debugging>.JsonSaveFile( m_FileName, this );
	}
	
	void Defaults()
	{
	}
	
	void Send( PlayerIdentity sendTo )
	{
		GetRPCManager().SendRPC( "CF", "LoadDebugging", new Param1< ref Debugging >( this ), false, sendTo );
	}
	
	/**
	\brief Saves and sends the debugging information
		@code
			GetDebugging().JM_CF_Mods = true;
			GetDebugging().Update();
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

static ref Debugging g_Debugging;

static ref Debugging GetDebugging()
{
	if ( !g_Debugging )
	{
		g_Debugging = Debugging.Load();
	}

	return g_Debugging;
}
