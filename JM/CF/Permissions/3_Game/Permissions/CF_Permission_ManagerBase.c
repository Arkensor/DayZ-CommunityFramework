typedef CF_Permission_ManagerBase JMPermissionManager;

class CF_Permission_ManagerBase
{
	protected ref map<string, ref CF_Permission_PlayerBase> Players;
	protected ref map<string, ref CF_Permission_Role> Roles;

	protected ref map<string, string> SteamToGUID;

	protected ref CF_Permission_Node RootPermission;

	protected string m_ClientGUID;

	static void _Init(out CF_Permission_ManagerBase pClass)
	{
		string strType = "CF_Permission_Manager";
		typename type = strType.ToType();
		pClass = CF_Permission_ManagerBase.Cast(type.Spawn());
		pClass.OnInit();
	}

	protected void OnInit()
	{
		Players = new map<string, ref CF_Permission_PlayerBase>;
		Roles = new map<string, ref CF_Permission_Role>;

		SteamToGUID = new map<string, string>;

		RootPermission = new CF_Permission_Node(__Constants.PERM_ROOT);

		if (IsMissionHost())
		{
			MakeDirectory(__Constants.DIR_PF);

			MakeDirectory(__Constants.DIR_PERMISSIONS);
			MakeDirectory(__Constants.DIR_PLAYERS);
			MakeDirectory(__Constants.DIR_ROLES);
		}

		Assert_Null(Players);
		Assert_Null(Roles);
		Assert_Null(SteamToGUID);
		Assert_Null(RootPermission);
	}

	void _Cleanup()
	{
		Assert_Null(Players);
		Assert_Null(Roles);
		Assert_Null(SteamToGUID);
		Assert_Null(RootPermission);

		delete Players;
		delete Roles;
		delete SteamToGUID;
		delete RootPermission;
	}

	void ResetMission()
	{
		Assert_Null(Players);
		Assert_Null(Roles);

		if (!IsMissionClient())
			return;

		Players.Clear();
		Roles.Clear();
	}

	void GetRolesAsList(out array<CF_Permission_Role> roles)
	{
	}

	void GetPermissionsAsList(out array<CF_Permission_Node> permissions)
	{
	}

	string GetClientGUID()
	{
		return m_ClientGUID;
	}

	void SetClientGUID(string guid)
	{
		m_ClientGUID = guid;
	}

	CF_Permission_PlayerBase GetClientPlayer()
	{
		return Players.Get(m_ClientGUID);
	}

	string ConvertGUIDToSteam(string uid)
	{
		return SteamToGUID.Get(uid);
	}

	ref CF_Permission_PlayerBase GetPlayer(string guid)
	{
		if (Assert_Null(Players))
			return null;

		return Players.Get(guid);
	}

	void Debug_CreatePlayers(int num)
	{
	}

	/**
     * @brief Returns an array of players based on the input GUID array
     * @code
     * array<CF_Permission_PlayerBase> players = CF.Permission.GetPlayers(guids);
     * @endcode
     *
     * @param array< string > guids					GUID array
     * @return array<CF_Permission_PlayerBase>		Array of players matching the guids
     */
	ref array<CF_Permission_PlayerBase> GetPlayers(ref array<string> guids = NULL)
	{
		return null;
	}

	/**
     * @brief Registers the permission, '.' delimited
     * @code
     * CF.Permission.Register("HypeTrain.Control");
     * @endcode
     *
     * @param pName									Permission to be registered
     * @return void
     */
	void Register(string pName)
	{
	}

	/**
	 * @deprecated
	 */
	void RegisterPermission(string permission)
	{
		Register(permission);
	}

	ref array<string> Serialize()
	{
		if (Assert_Null(RootPermission))
			return new array<string>();

		ref array<string> data = new array<string>;
		RootPermission.Serialize(data);
		return data;
	}

	ref CF_Permission_Node GetRootPermission()
	{
		Assert_Null(RootPermission);

		return RootPermission;
	}

	/**
     * @brief On the client (/singleplayer), check for permission
     * @code
     * CF.Permission.HasPermission("HypeTrain.Control");
     * @endcode
     *
     * @param permission							Permission to be checked for
     * @return bool									Has permission
     */
	bool HasPermission(string permission)
	{
		return false;
	}

	/**
     * @brief Check if the identity has permission
     * @code
     * CF.Permission.HasPermission("HypeTrain.Control");
     * @endcode
     *
     * @param permission							Permission to be checked for
     * @param identity								Identity of the player
     * @return bool									Has permission
     */
	bool HasPermission(string permission, PlayerIdentity ihp)
	{
		return false;
	}

	/**
     * @brief Check if the identity has permission, out CF_Permission_PlayerBase
     * @code
     * CF.Permission.HasPermission("HypeTrain.Control");
     * @endcode
     *
     * @param permission							Permission to be checked for
     * @param identity								Identity of the player
     * @param[out] player							Player to be returned
     * @return bool									Has permission
     */
	bool HasPermission(string permission, PlayerIdentity identity, out CF_Permission_PlayerBase player)
	{
		return false;
	}

	bool OnClientConnected(PlayerIdentity ident, out CF_Permission_PlayerBase player)
	{
		return false;
	}

	bool OnClientDisconnected(string guid, out CF_Permission_PlayerBase player)
	{
		return false;
	}

	ref CF_Permission_PlayerBase UpdatePlayer(string guid, ref ParamsReadContext ctx, DayZPlayer playerUpdatePlayer = NULL)
	{
		return null;
	}

	CF_Permission_Role CreateRole(string name, ref array<string> data)
	{
		return null;
	}

	bool LoadRole(string name, out CF_Permission_Role role)
	{
		role = null;
		return false;
	}

	CF_Permission_Role GetRole(string name)
	{
		if (Assert_Null(Roles))
			return null;

		return Roles.Get(name);
	}

	CF_Permission_Role GetRole(int index)
	{
		if (Assert_Null(Roles))
			return null;

		return Roles.GetElement(index);
	}

	bool RoleExists(string role)
	{
		return Roles.Contains(role);
	}

	bool IsRole(string role)
	{
		return Roles.Contains(role);
	}

	int RoleCount()
	{
		return Roles.Count();
	}

	protected bool IsValidFolderForRoles(string name, FileAttr attributes)
	{
		string extenstion = ".txt";
		int strLength = name.Length();

		if (name == extenstion)
			return false;

		if (attributes & FileAttr.DIRECTORY)
			return false;

		if (name == "")
			return false;

		return true;
	}
};

/**
 * @deprecated
 */
ref CF_Permission_ManagerBase GetPermissionsManager()
{
	return CF.Permission;
}