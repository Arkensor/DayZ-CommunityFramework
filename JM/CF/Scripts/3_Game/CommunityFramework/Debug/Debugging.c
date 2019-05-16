class Debugging
{
    bool JM_CF_Mods = true;
	bool JM_CF_RPC = true;
	bool JM_CF_Credits = true;
	
	void Log( string text, string type )
	{
		bool printOut = false;
		
		int success = EnScript.GetClassVar( this, type, 0, printOut );
		
		if ( success != 0 && printOut )
		{
			Print( "" + text );
		}
	}
}

static ref Debugging g_Debugging;

static ref Debugging GetDebugging()
{
    if ( !g_Debugging )
    {
        g_Debugging = new ref Debugging;
    }

    return g_Debugging;
}
