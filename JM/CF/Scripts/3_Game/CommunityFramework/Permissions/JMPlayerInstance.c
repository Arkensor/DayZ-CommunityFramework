class JMPlayerInstance : Managed
{
	private ref JMPermission m_RootPermission;
	private ref array< string > m_Roles;

	DayZPlayer PlayerObject;

	private int m_DataLastUpdated;

	private string m_Name;
	private string m_GUID;
	private string m_Steam64ID;

	private int m_PingMax;
	private int m_PingMin;
	private int m_PingAvg;

	private ref JMPlayerSerialize m_PlayerFile;

	void JMPlayerInstance( PlayerIdentity identity )
	{
		PlayerObject = NULL;

		if ( identity && GetGame().IsServer() )
		{
			m_GUID = identity.GetId();
			m_Steam64ID = identity.GetPlainId();
			m_Name = identity.GetName();
		} else if ( IsMissionOffline() )
		{
			m_GUID = __Constants.OFFLINE_GUID;
			m_Steam64ID = __Constants.OFFLINE_STEAM;
			m_Name = __Constants.OFFLINE_NAME;
		}

		m_RootPermission = new JMPermission( __Constants.PERM_ROOT );
		m_Roles = new array< string >();
		m_PlayerFile = new JMPlayerSerialize();
	}

	void ~JMPlayerInstance()
	{
		Assert_Null( m_RootPermission );
		Assert_Null( m_Roles );
		Assert_Null( m_PlayerFile );

		delete m_RootPermission;
		delete m_Roles;
		delete m_PlayerFile;
	}

	void MakeFake( string gid, string sid, string nid )
	{
		m_GUID = gid;
		m_Steam64ID = sid;
		m_Name = nid;
	}

	bool CanSendData()
	{
		return PlayerObject != NULL; 
	}

	void Update()
	{
		if ( GetGame().IsServer() && ( GetGame().GetTime() - m_DataLastUpdated ) >= 100 )
		{
			if ( !GetGame().IsMultiplayer() )
			{
				Class.CastTo( PlayerObject, GetGame().GetPlayer() );
			}

			if ( PlayerObject )
			{
				m_DataLastUpdated = GetGame().GetTime();

				OnUpdateData();
			}
		}
	}
	
	void OnUpdateData()
	{
	}

	void CopyPermissions( ref JMPermission copy )
	{
		Assert_Null( m_RootPermission );
		Assert_Null( copy );

		array< string > data = new array< string >;

		copy.Serialize( data );

		m_RootPermission.Deserialize( data );
	}

	void ClearPermissions()
	{
		Assert_Null( m_RootPermission );

		m_RootPermission.Clear();
	}

	void LoadPermissions( array< string > permissions )
	{
		Assert_Null( m_RootPermission );

		m_RootPermission.Deserialize( permissions );
		Save();
	}

	void AddPermission( string permission, JMPermissionType type = JMPermissionType.INHERIT )
	{
		Assert_Null( m_RootPermission );

		m_RootPermission.AddPermission( permission, type );
	}

	void LoadRoles( notnull array< string > roles )
	{
		ClearRoles();

		for ( int i = 0; i < roles.Count(); i++ )
		{
			AddRole( roles[i] );
		}

		Save();
	}

	void AddRole( string role )
	{
		Assert_Null( GetPermissionsManager() );
		Assert_Null( m_Roles );

		if ( !GetPermissionsManager().IsRole( role ) )
			return;

		if ( m_Roles.Find( role ) < 0 )
		{
			m_Roles.Insert( role );
		}
	}

	bool HasRole( string role )
	{
		return m_Roles.Find( role ) >= 0;
	}

	// doesn't check through roles.
	JMPermissionType GetRawPermissionType( string permission )
	{
		Assert_Null( m_RootPermission );

		JMPermissionType permType;
		m_RootPermission.HasPermission( permission, permType );
		return permType;
	}

	void ClearRoles()
	{
		m_Roles.Clear();

		AddRole( "everyone" );
	}

	bool HasPermission( string permission )
	{
		Assert_Null( m_RootPermission );
		
		JMPermissionType permType;
		bool hasPermission = m_RootPermission.HasPermission( permission, permType );
		
		// Print( "JMPlayerInstance::HasPermission - hasPermission=" + hasPermission );
		if ( hasPermission )
		{
			return true;
		}

		// Print( "JMPlayerInstance::HasPermission - permType=" + permType );
		if ( permType == JMPermissionType.DISALLOW )
		{
			return false;
		}

		for ( int j = 0; j < m_Roles.Count(); j++ )
		{
			JMRole role = GetPermissionsManager().GetRole( m_Roles[j] );
			if ( !role )
				continue;

			hasPermission = role.HasPermission( permission, permType );

			// Print( "JMPlayerInstance::HasPermission - role[" + j + "]=" + Roles[j] );
			// Print( "JMPlayerInstance::HasPermission - permType=" + permType );
			// Print( "JMPlayerInstance::HasPermission - hasPermission=" + hasPermission );

			if ( hasPermission )
				return true;
		}

		return false;
	}

	void OnSend( ref ParamsWriteContext ctx /* param here for helper class so only necessary data is filled based on permissions */ )
	{
		ctx.Write( m_GUID );
		ctx.Write( m_Steam64ID );
		ctx.Write( m_Name );
	}

	void OnRecieve( ref ParamsReadContext ctx )
	{
		ctx.Read( m_GUID );
		ctx.Read( m_Steam64ID );
		ctx.Read( m_Name );
	}

	void OnSendPermissions( ref ParamsWriteContext ctx )
	{
		Assert_Null( m_RootPermission );

		array< string > permissions = new array< string >;
		m_RootPermission.Serialize( permissions );

		ctx.Write( permissions );
		ctx.Write( m_Roles );
	}

	void OnRecievePermissions( ref ParamsReadContext ctx )
	{
		Assert_Null( m_RootPermission );
		
		array< string > permissions = new array< string >;
		array< string > roles = new array< string >;

		ctx.Read( permissions );
		ctx.Read( roles );

		m_RootPermission.Deserialize( permissions );
		
		ClearRoles();
		for ( int j = 0; j < roles.Count(); j++ )
			AddRole( roles[j] );
	}

	void Save()
	{
		Assert_Null( m_RootPermission );
		if ( !Assert_Null( m_PlayerFile ) )
			Assert_Null( m_PlayerFile.Roles );

		if ( !GetGame().IsServer() )
			return;

		array< string > permissions = new array< string >;
		m_RootPermission.Serialize( permissions );

		m_PlayerFile.Roles.Clear();
		m_PlayerFile.Roles.Copy( m_Roles );
		m_PlayerFile.Save();

		FileHandle file = OpenFile( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_GUID ) + __Constants.EXT_PERMISSION, FileMode.WRITE );
		if ( file != 0 )
		{
			string line;
			for ( int i = 0; i < permissions.Count(); i++ )
			{
				FPrintln( file, permissions[i] );
			}
			
			CloseFile( file );
		}
	}

	string FileReadyStripName( string name )
	{
		name.Replace( "\\", "" );
		name.Replace( "/", "" );
		name.Replace( "=", "" );
		name.Replace( "+", "" );

		return name;
	}

	protected bool ReadPermissions( string filename )
	{
		Assert_Null( m_RootPermission );

		if ( !FileExist( filename ) )
			return false;

		FileHandle file = OpenFile( filename, FileMode.READ );

		if ( file < 0 )
			return false;

		array< string > data = new array< string >;

		string line;

		while ( FGets( file, line ) > 0 )
		{
			data.Insert( line );
		}

		CloseFile( file );

		for ( int i = 0; i < data.Count(); i++ )
		{
			AddPermission( data[i] );
		}

		return true;
	}

	void Load()
	{
		Assert_Null( m_PlayerFile );

		if ( !IsMissionHost() )
			return;

		Update();

		JMPlayerSerialize.Load( this, m_PlayerFile );

		for ( int j = 0; j < m_PlayerFile.Roles.Count(); j++ )
		{
			AddRole( m_PlayerFile.Roles[j] );
		}

		if ( !ReadPermissions( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_GUID ) + __Constants.EXT_PERMISSION ) )
		{
			if ( ReadPermissions( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_GUID ) + __Constants.EXT_PERMISSION + __Constants.EXT_WINDOWS_DEFAULT ) )
			{
				DeleteFile( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_GUID ) + __Constants.EXT_PERMISSION + __Constants.EXT_WINDOWS_DEFAULT );
			} else if ( ReadPermissions( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_Steam64ID ) + __Constants.EXT_PERMISSION ) )
			{
				DeleteFile( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_Steam64ID ) + __Constants.EXT_PERMISSION );
			} else if ( ReadPermissions( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_Steam64ID ) + __Constants.EXT_PERMISSION + __Constants.EXT_WINDOWS_DEFAULT ) )
			{
				DeleteFile( __Constants.DIR_PERMISSIONS + FileReadyStripName( m_Steam64ID ) + __Constants.EXT_PERMISSION + __Constants.EXT_WINDOWS_DEFAULT );
			}
		}

		Save();
	}

	void DebugPrint()
	{
		// Print( "  SGUID: " + m_GUID );
		// Print( "  SSteam64ID: " + m_Steam64ID );
		// Print( "  SName: " + m_Name );

		m_RootPermission.DebugPrint( 2 );
	}

	string GetGUID()
	{
		return m_GUID;
	}

	string GetSteam64ID()
	{
		return m_Steam64ID;
	}

	string GetName()
	{
		return m_Name;
	}

	string FormatSteamWebhook()
	{
		return "[" + m_Name + "](https://steamcommunity.com/profiles/" + m_Steam64ID + ")";
	}

	int GetMaxPing()
	{
		return m_PingMax;
	}

	int GetMinPing()
	{
		return m_PingMin;
	}

	int GetAvgPing()
	{
		return m_PingAvg;
	}
};