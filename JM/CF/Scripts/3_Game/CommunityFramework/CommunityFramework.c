CGame CF_CreateGame()
{
	// Already assigns 'g_Game'
	CreateGame();
	
	CF._GameInit();
	
	return g_Game;
}

enum CF_ResolvePath
{
	MISSION,
	PROFILE,
	SAVES,
	STORAGE
}

typedef CommunityFramework CF;
class CommunityFramework : ModStructure
{
    static CF_ObjectManager ObjectManager;
	static CF_XML XML;
	static bool s_FindFile_DZ130_Tested;
	static bool s_FindFileEx_ResolvePath;
	static string s_MissionFolder;
	static string s_ProfileFolder;
	static string s_SavesFolder;
	static string s_StorageFolder;

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
		err = string.Format(err, p1, p2, p3, p4, p5, p6, p7, p8, p9);

		if (severity != ErrorExSeverity.INFO)
		{
			ErrorEx(err, severity);
		}
		else
		{
			string stack;
			DumpStackString(stack);

			TStringArray lines = {};
			stack.Split("\n", lines);

			string caller = lines[1];

			int lastIndex = caller.LastIndexOf("/") + 1;
			string filename = caller.Substring(lastIndex, caller.LastIndexOf(":") - 1 - lastIndex);
			string funcname = caller.Substring(0, caller.IndexOf("("));
			
			PrintFormat("[%1::%2] :: [INFO] :: %3", filename, funcname, err);
		}
	}

	/**
	 * @brief Resolves filesystem prefixes ('$mission', '$profile', '$saves', '$storage') in path.
	 * Guessing might be involved.
	 *
	 * @note only works if the respective directories are under the game directory
	 *
	 * @return path with prefixes resolved (relative to game directory) and all backslashes converted to forward slashes
	 */
	static string ResolvePath(string path)
	{
		path.Replace("\\", "/");  //! Important, have to use fwd slash not backslash, won't find files otherwise under 1.30

		string pathLower = path;
		pathLower.ToLower();

		int resolve;
		int lastCharIdx;
		string relPath;

		if (pathLower.IndexOf("$profile:") == 0)
			resolve = CF_ResolvePath.PROFILE;
		else if (pathLower.IndexOf("$saves:") == 0)
			resolve = CF_ResolvePath.SAVES;
		else if (pathLower.IndexOf("$mission:") == 0)
			resolve = CF_ResolvePath.MISSION;
		else if (pathLower.IndexOf("$storage:") == 0)
			resolve = CF_ResolvePath.STORAGE;

		if (resolve == CF_ResolvePath.PROFILE || resolve == CF_ResolvePath.SAVES)
		{
			if (!s_ProfileFolder)
			{
				string profileParam;
				if (GetCLIParam("profiles", profileParam))
				{
					profileParam.Replace("\\", "/");  //! Important, have to use fwd slash not backslash, won't find files otherwise under 1.30

					lastCharIdx = profileParam.Length() - 1;
					if (profileParam[lastCharIdx] == "/")
						profileParam = profileParam.Substring(0, lastCharIdx);

				#ifdef DIAG_DEVELOPER
					FormatErrorEx( "Profile param %1", ErrorExSeverity.INFO, profileParam);
				#endif

					int index = profileParam.LastIndexOf("/");
					if (index > -1)
						profileParam = profileParam.Substring(index + 1, profileParam.Length() - index - 1);

					s_ProfileFolder = profileParam;
					
					if (!s_ProfileFolder)
					{
						Error("Could not determine profile folder, please use -profiles parameter");
					}
					else if (!FileExist(s_ProfileFolder))
					{
						FormatError("Profile folder %1 does not exist inside game directory", s_ProfileFolder);
					}
					else
					{
						FormatErrorEx("Using profile folder %1", ErrorExSeverity.INFO, s_ProfileFolder);
					}
				}
			}

			if (s_ProfileFolder)
			{
				if (resolve == CF_ResolvePath.PROFILE)
				{
					relPath = path.Substring(9, path.Length() - 9);
					path = string.Format("%1/%2", s_ProfileFolder, relPath);
				}
				else if (resolve == CF_ResolvePath.SAVES)
				{
					if (!s_SavesFolder)
					{
						string userName;
					#ifdef SERVER
						userName = "Server";
					#else
						BiosUserManager userMgr = g_Game.GetUserManager();
						if (userMgr)
						{
							BiosUser user = userMgr.GetSelectedUser();
							if (user)
								userName = user.GetName();
						}
					#endif

						s_SavesFolder = string.Format("%1/Users/%2", s_ProfileFolder, userName);
					}

					relPath = path.Substring(7, path.Length() - 7);
					path = string.Format("%1/%2", s_SavesFolder, relPath);
				}
			}
		}
		else if (resolve == CF_ResolvePath.MISSION || resolve == CF_ResolvePath.STORAGE)
		{
			if (!s_MissionFolder)
			{
				string missionParam;
				if (GetCLIParam("mission", missionParam))
				{
					missionParam.Replace("\\", "/");  //! Important, have to use fwd slash not backslash, won't find files otherwise under 1.30

					lastCharIdx = missionParam.Length() - 1;
					if (missionParam[lastCharIdx] == "/")
						missionParam = missionParam.Substring(0, lastCharIdx);

				#ifdef DIAG_DEVELOPER
					FormatErrorEx("Mission param %1", ErrorExSeverity.INFO, missionParam);
				#endif

					s_MissionFolder = missionParam;
				}
				else
				{
					string configParam;
					if (GetCLIParam("config", configParam))
					{
						if (FileExist(configParam))
						{
							ConfigFile cfg = ConfigFile.Parse(configParam);
							if (cfg)
							{
								ConfigEntry entry = cfg.Get("Missions DayZ template");
								if (entry)
									s_MissionFolder = entry.GetText();
							}
						}
					}

					if (!s_MissionFolder)
					{
						//! Best we can do with what we have is guess from world name
						string worldName;
						g_Game.GetWorldName(worldName);

						TStringArray candidates = {};

						candidates.Insert(string.Format("mpmissions/dayzOffline.%1", worldName));
						candidates.Insert(string.Format("mpmissions/empty.%1", worldName));
						candidates.Insert(string.Format("mpmissions/hardcore.%1", worldName));
						candidates.Insert(string.Format("mpmissions/main.%1", worldName));
						candidates.Insert(string.Format("mpmissions/offline.%1", worldName));
						candidates.Insert(string.Format("mpmissions/regular.%1", worldName));
						candidates.Insert(string.Format("mpmissions/summer.%1", worldName));

						foreach (string candidate: candidates)
						{
							if (FileExist(candidate))
							{
								s_MissionFolder = candidate;
								break;
							}
						}
					}
				}

				if (!s_MissionFolder)
				{
					Error("Could not determine mission folder, please use -mission parameter");
				}
				else if (!FileExist(s_MissionFolder))
				{
					FormatError("Mission folder %1 does not exist inside game directory", s_MissionFolder);
				}
				else
				{
					FormatErrorEx("Using mission folder %1", ErrorExSeverity.INFO, s_MissionFolder);
				}
			}

			if (s_MissionFolder)
			{
				if (resolve == CF_ResolvePath.MISSION)
				{
					relPath = path.Substring(9, path.Length() - 9);
					path = string.Format("%1/%2", s_MissionFolder, relPath);
				}
				else if (resolve == CF_ResolvePath.STORAGE)
				{
					if (!s_StorageFolder)
					{
						int instanceId = g_Game.ServerConfigGetInt("instanceId");
						s_StorageFolder = string.Format("%1/storage_%2", s_MissionFolder, instanceId);
						FormatErrorEx("Using storage folder %1", ErrorExSeverity.INFO, s_StorageFolder);
					}

					relPath = path.Substring(9, path.Length() - 9);
					path = string.Format("%1/%2", s_StorageFolder, relPath);
				}
			}
		}
		else if (pathLower.IndexOf("$currentdir:") == 0)
		{
			path = path.Substring(12, path.Length() - 12);
		}
		
		return path;
	}

	static FindFileHandle FindFileEx(string pattern, out string fileName, out FileAttr fileAttributes, FindFileFlags flags)
	{
		pattern.Replace("\\", "/");  //! Important, have to use fwd slash not backslash, won't find files otherwise under 1.30

	#ifndef DAYZ_1_29
		//! 1.30 Experimental broke $ placeholders and bwd slash usage in FindFile, see https://report.bistudio.com/issues/DZEXP-134
		//! Since this will be fixed later on 1.30 stable, test if we can read from mission dir. If we can't, apply our workaround
		//! by resolving filesystem prefixes ourselves.
		if (!s_FindFile_DZ130_Tested)
		{
			string testFileName = "cf_findfile_dz130_test";
			string testPath = string.Format("$profile:%1", testFileName);

			if (!FileExist(testPath))
			{
				FileHandle testFile = OpenFile(testPath, FileMode.WRITE);
				CloseFile(testFile);
			}
			
			FindFileHandle findFileHandle = FindFile(testPath, fileName, fileAttributes, FindFileFlags.ALL);
			if (!findFileHandle || fileName != testFileName)
				s_FindFileEx_ResolvePath = true;

			s_FindFile_DZ130_Tested = true;
		}

		if (s_FindFileEx_ResolvePath)
			pattern = ResolvePath(pattern);
	#endif

		return FindFile(pattern, fileName, fileAttributes, flags);
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
	if ( !g_Game )
		return false;

	return g_Game.IsServer() || !g_Game.IsMultiplayer();
}

static bool IsMissionClient()
{
	if ( !g_Game )
		return false;

	return g_Game.IsClient() || !g_Game.IsMultiplayer();
}

static bool IsMissionOffline()
{
	if ( !g_Game )
		return false;

	return g_Game.IsServer() && !g_Game.IsMultiplayer();
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