CGame CF_CreateGame()
{
	Print("CF_CreateGame()");
	g_Game = new DayZGame;
	CF._GameInit(true);
	return g_Game;
}

void CF_CreateWorld()
{
	Print("CF_CreateWorld()");
	CF._WorldInit();
}

typedef CommunityFramework CF;

class CommunityFramework
{
    static CF_ObjectManager ObjectManager;
	static CF_XML XML;

    static CF_Log Log;
    static CF_Trace Trace;

    static ref CF_MVVM MVVM;
    static ref CF_TypeConverters TypeConverters;

    #ifdef CF_WINDOWS
    static ref CF_Windows Windows;
    #endif

	#ifdef CF_MODULE_PERMISSIONS
	static ref CF_Permission_ManagerBase Permission;
	#endif

    static DayZGame Game()
    {
        #ifdef COMPONENT_SYSTEM 
        if (!g_Game)
        {
            CF_CreateGame();
        }
        #endif

        return g_Game;
    }

    /**
     * @brief [Internal] CommunityFramework initilization for 3_Game
     *
     * @return void
     */
	static void _GameInit(bool realInit = false)
	{
        if (!realInit) Game();

        TypeConverters = TypeConverters._Init();
        MVVM = MVVM._Init();
        
        #ifdef CF_WINDOWS
        Windows = Windows._Init();
        #endif

        Log._Init();
	}

    /**
     * @brief [Internal] CommunityFramework initilization for 4_World
     *
     * @return void
     */
	static void _WorldInit()
	{
		#ifdef CF_MODULE_PERMISSIONS
		CF_Permission_ManagerBase._Init( Permission );
		#endif
	}

    static void _MissionInit()
    {
        #ifdef CF_WINDOWS
		CF.Windows._MissionInit();
        #endif
    }

    static void _MissionCleanup()
    {
        #ifdef CF_WINDOWS
		CF.Windows._MissionCleanup();
        #endif
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

        MVVM._Cleanup();
        Windows._Cleanup();

		#ifdef CF_MODULE_PERMISSIONS
		Permission._Cleanup();
		#endif

        Log._Cleanup();
    }

    static bool StringToBool(string str)
    {
        str.ToLower();
        str.Trim();
        if (str == "true") return true;
        if (str == "false") return false;
        return str.ToInt();
    }
};

//--------------------------------------------------------

const autoptr TStringArray _cf_characters = {
//		"",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
//        "",
        " ",
        "!",
        "\"",
        "#",
        "$",
        "%",
        "&",
        "\'",
        "(",
        ")",
        "*",
        "+",
        ",",
        "-",
        ".",
        "/",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        ":",
        ";",
        "<",
        "=",
        ">",
        "?",
        "@",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "[",
        "\\",
        "]",
        "^",
        "_",
        "`",
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "{",
        "|",
        "}",
        "~",
        ""
    };

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



static void Assert_Log( string str )
{
	Print( "==============================================WARNING=======================================================" );
	string time = JMDate.Now( false ).ToString( "YYYY-MM-DD hh:mm:ss" );
	Print( "[WARNING " + time + "] " + str );
	Print( "Do you see this message? Unless the time is within a second of the crash than this was not the cause." );

	DumpStack();

	Print( "============================================================================================================" );
}

static bool Assert_Empty( string str, string message = "" )
{
	if ( str == "" )
	{
		if ( message != "" )
			message = ": " + message;

		Assert_Log( "ASSERTION STRING EMPTY" + message );
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

		Assert_Log( "ASSERTION NULL" + message );
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

		Assert_Log( "ASSERTION FALSE" + message );
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

		Assert_Log( "ASSERTION TRUE" + message );
		return true;
	}
	
	return false;
}