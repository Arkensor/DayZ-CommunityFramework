CGame CF_CreateGame()
{
	// Already assigns 'g_Game'
	CreateGame();
	
	CF._GameInit();
	
	return g_Game;
}

typedef CommunityFramework CF;
class CommunityFramework : ModStructure
{
    static CF_ObjectManager ObjectManager;
	static CF_XML XML;

    /**
     * @brief [Internal] CommunityFramework initilization for 3_Game
     *
     * @return void
     */
	static void _GameInit()
	{
	}

    /**
     * @brief [Internal] CommunityFramework cleanup
     *
     * @return void
     */
    static void _Cleanup()
    {
        ObjectManager._Cleanup();
		XML._Cleanup();
    }

    /**
     * @brief Checks if the game is host
     */
    static bool IsMissionHost()
    {
	    if (!g_Game) return false;

	    return g_Game.IsServer() || !g_Game.IsMultiplayer();
    }

    /**
     * @brief Checks if the game is client
     */
    static bool IsMissionClient()
    {
	    if (!g_Game) return false;

	    return g_Game.IsClient() || !g_Game.IsMultiplayer();
    }

    /**
     * @brief Checks if the game is singleplayer
     */
    static bool IsMissionOffline()
    {
	    if (!g_Game) return false;

	    return g_Game.IsServer() && !g_Game.IsMultiplayer();
    }

    /**
     * @brief Check if calling function is in list
	 * 
	 * @param callers   List of callers (function names)
	 * @param logError  If true, logs error if caller not in list
	 * 
	 * @return true if in list, false if not
	 * 
	 * @note Use sparsely (performance impact) and only to communicate intent
	 * 
	 * @code
	 * class ExampleA
	 * {
	 *     void Poke()
	 *     {
	 *         if (CF.IsCallFrom({"PokeOther"}))
	 *             Print("Hello friend");
	 *         else
	 *             Print("I don't know you");
	 *     }
	 * }
	 * 
	 * class ExampleB
	 * {
	 *     void PokeOther(ExampleA other)
	 *     {
	 *         other.Poke();  // OK
	 *     }
	 * 
	 *     void PokeOther2(ExampleA other)
	 *     {
	 *         other.Poke();  // Error
	 *     }
	 * }
	 * @endcode
     */
	static bool IsCallFrom(TStringArray callers, bool logError = true)
	{
		string tmp;
		DumpStackString(tmp);
		TStringArray stack = {};
		tmp.Split("\n", stack);

		foreach (string caller: callers)
		{
			if (stack[2].IndexOf(caller + "() ") == 0)
				return true;
		}

		if (logError)
			CF_Log.Error("Invalid caller.");

		return false;
	}

	static void FormatError(string err, string p1 = "", string p2 = "", string p3 = "", string p4 = "", string p5 = "", string p6 = "", string p7 = "", string p8 = "", string p9 = "")
	{
		Error(string.Format(err, p1, p2, p3, p4, p5, p6, p7, p8, p9));
	}

	static void FormatErrorEx(string err, ErrorExSeverity severity = ErrorExSeverity.ERROR, string p1 = "", string p2 = "", string p3 = "", string p4 = "", string p5 = "", string p6 = "", string p7 = "", string p8 = "", string p9 = "")
	{
		ErrorEx(string.Format(err, p1, p2, p3, p4, p5, p6, p7, p8, p9));
	}
};

class JM_CommunityFramework : CommunityFramework
{

};

//--------------------------------------------------------

//TODO: remove this when the CF refactor is completed
static string CF_XML_Indent( int level )
{
	string str = "";

	for ( int i = 0; i < level; ++i )
		str += "\t";

	return str;
}

static bool IsMissionHost()
{
	if ( !GetGame() )
		return false;

	return GetGame().IsServer() || !GetGame().IsMultiplayer();
}

static bool IsMissionClient()
{
	if ( !GetGame() )
		return false;

	return GetGame().IsClient() || !GetGame().IsMultiplayer();
}

static bool IsMissionOffline()
{
	if ( !GetGame() )
		return false;

	return GetGame().IsServer() && !GetGame().IsMultiplayer();
}

static string CF_Indent( int level )
{
	string str = "";

	for ( int i = 0; i < level; ++i )
		str += "  ";

	return str;
}

static void CF_DumpWidgets( Widget root, int tabs = 0 )
{
	if ( !root )
	{
		return;
	}
	
	string tmp;
	for ( int i = 0; i < tabs; i++ )
	{
		tmp += "  ";
	}
	
	string invisible = "";
	
	if ( !root.IsVisibleHierarchy() )
	{
		invisible = "[invisible]";
	}
	
	Print( tmp + "- " + root.GetName() + " (" + root.GetTypeName() + ") " + invisible );
	
	bool collapse = false;
	if ( root.GetChildren() )
	{
		collapse = true;
		Print( tmp + "{" );
	}
	
	CF_DumpWidgets( root.GetChildren(), tabs + 1 );
		
	if ( collapse )
	{
		Print( tmp + "}" );
	}
			
	CF_DumpWidgets( root.GetSibling(), tabs );
}



static void Assert_Log( string str, int offset = 1 )
{
	Print( "==============================================WARNING=======================================================" );
	string time = CF_Date.Now( false ).Format( CF_Date.DATETIME );
	Print( "[WARNING " + time + "] " + str );
	Print( "Do you see this message? Unless the time is within a second of the crash than this was not the cause." );
    
	string dump = "";
	DumpStackString(dump);
	array<string> outputs = new array<string>();
	dump.Split("\n", outputs);

	for (int i = offset; i < outputs.Count(); i++)
	{
		Print("\t" + outputs[i]);
	}

	Print( "============================================================================================================" );
}

static bool Assert_Empty( string str, string message = "" )
{
	if ( str == "" )
	{
		if ( message != "" )
			message = ": " + message;

		Assert_Log( "ASSERTION STRING EMPTY" + message, 2 );
		return true;
	}
	
	return false;
}

static bool Assert_Null( Class cls, string message = "" )
{
	if ( cls == NULL )
	{
		if ( message != "" )
			message = ": " + message;

		Assert_Log( "ASSERTION NULL" + message, 2 );
		return true;
	}
	
	return false;
}

static bool Assert_False( bool cls, string message = "" )
{
	if ( cls == false )
	{
		if ( message != "" )
			message = ": " + message;

		Assert_Log( "ASSERTION FALSE" + message, 2 );
		return true;
	}
	
	return false;
}

static bool Assert_True( bool cls, string message = "" )
{
	if ( cls == true )
	{
		if ( message != "" )
			message = ": " + message;

		Assert_Log( "ASSERTION TRUE" + message, 2 );
		return true;
	}
	
	return false;
}