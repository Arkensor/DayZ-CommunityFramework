class Debugging
{
	[NonSerialized()]
	string m_FileName;
	
	bool JM_CF_Mods;
	bool JM_CF_RPC;
	bool JM_CF_Credits;
	bool JM_CF_KeyBindings;
	
	private void Debugging()
	{
		m_FileName = "$profile:Debugging.json";
	}

	void Log( string text, string type )
	{
		bool printOut = false;
		
		int success = EnScript.GetClassVar( this, type, 0, printOut );
		
		if ( success == 0 && printOut )
		{
			Print( "" + text );
		}
	}
	
	void Err( string text, string type )
	{
		bool printOut = false;
		
		int success = EnScript.GetClassVar( this, type, 0, printOut );
		
		if ( success == 0 && printOut )
		{
			Print( "" + text );
		}
		
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
		Send( NULL );
		Save();
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
