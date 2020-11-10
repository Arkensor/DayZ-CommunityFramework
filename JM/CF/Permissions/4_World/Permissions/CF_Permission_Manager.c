class CF_Permission_Manager : CF_Permission_ManagerBase
{
	override void GetRolesAsList(out array<CF_Permission_Role> roles)
	{
		if (Assert_Null(Roles))
			return;

		if (!roles)
			roles = new array<CF_Permission_Role>();

		roles.Copy(Roles.GetValueArray());
	}

	override void GetPermissionsAsList(out array<CF_Permission_Node> permissions)
	{
		if (Assert_Null(RootPermission))
			return;

		if (!permissions)
			permissions = new array<CF_Permission_Node>();

		GetPermissionsAsList(RootPermission, -1, permissions);
	}

	private void GetPermissionsAsList(ref CF_Permission_Node permission, int depth, inout array<CF_Permission_Node> permissions)
	{
		if (Assert_Null(RootPermission) || Assert_Null(permission))
			return;

		permission.Depth = depth;

		for (int i = 0; i < permission.Children.Count(); ++i)
		{
			permissions.Insert(permission.Children[i]);

			GetPermissionsAsList(permission.Children[i], depth + 1, permissions);
		}
	}

	override void Debug_CreatePlayers(int num)
	{
		for (int i = 0; i < num; i++)
		{
			CF_Permission_PlayerBase instance = new CF_Permission_Player(NULL);
			instance.MakeFake("GFake" + i, "SFake" + i, "NFake" + i);
			Players.Insert(instance.GetGUID(), instance);
		}
	}

	override ref array<CF_Permission_PlayerBase> GetPlayers(ref array<string> guids = NULL)
	{
		if (Assert_Null(Players))
			return new array<CF_Permission_PlayerBase>();

		if (guids == NULL || !GetGame().IsMultiplayer())
		{
			return Players.GetValueArray();
		}

		array<CF_Permission_PlayerBase> players();

		for (int i = 0; i < guids.Count(); i++)
		{
			CF_Permission_PlayerBase instance = Players.Get(guids[i]);
			if (Assert_Null(instance))
				continue;

			players.Insert(instance);
		}

		return players;
	}

	override void Register(string pName)
	{
		Assert_Null(RootPermission);

		RootPermission.AddPermission(pName, CF_Permission_Type.INHERIT);
	}

	ref array<string> Serialize()
	{
		Assert_Null(RootPermission);

		ref array<string> data = new array<string>;
		RootPermission.Serialize(data);
		return data;
	}

	ref CF_Permission_Node GetRootPermission()
	{
		Assert_Null(RootPermission);

		return RootPermission;
	}

	override bool HasPermission(string permission)
	{
		if (IsMissionClient())
		{
			if (IsMissionHost())
				return true;

			CF_Permission_PlayerBase instance = GetClientPlayer();
			if (!instance)
				return false;

			return instance.HasPermission(permission);
		}

		Error("CF_Permission_Manager::HasPermission( permission = " + permission + " ) bool; was called on server!");

		return false;
	}

	override bool HasPermission(string permission, PlayerIdentity ihp)
	{
		if (IsMissionOffline())
			return true;

		CF_Permission_PlayerBase instance;
		return HasPermission(permission, ihp, instance);
	}

	override bool HasPermission(string permission, PlayerIdentity identity, out CF_Permission_PlayerBase player)
	{
		if (IsMissionClient())
		{
			player = GetClientPlayer();

			if (IsMissionHost())
				return true;

			if (Assert_Null(player))
				return false;

			return player.HasPermission(permission);
		}

		if (Assert_Null(identity))
		{
			Print("Player identity does not exist.");
			return false;
		}

		player = Players.Get(identity.GetId());
		if (Assert_Null(player))
		{
			Print("CF_Permission_PlayerBase does not exist for " + identity.GetId());
			return false;
		}

		return player.HasPermission(permission);
	}

	override bool OnClientConnected(PlayerIdentity ident, out CF_Permission_PlayerBase player)
	{
		if (Assert_Null(RootPermission) || Assert_Null(Players))
			return false;

		if (ident == NULL)
			return !GetGame().IsMultiplayer();

		string guid = ident.GetId();

		SteamToGUID.Insert(ident.GetPlainId(), guid);

		player = Players.Get(guid);
		if (player)
			return false;

		player = new CF_Permission_Player(ident);

		player.CopyPermissions(RootPermission);
		player.Load();

		Players.Insert(guid, player);

		return true;
	}

	override bool OnClientDisconnected(string guid, out CF_Permission_PlayerBase player)
	{
		if (Assert_Null(Players))
			return false;

		player = Players.Get(guid);
		if (!player)
			return false;

		player.Save();

		Players.Remove(guid);
		return true;
	}

	override ref CF_Permission_PlayerBase UpdatePlayer(string guid, ref ParamsReadContext ctx, DayZPlayer playerUpdatePlayer = NULL)
	{
		CF_Permission_PlayerBase instance = GetPlayer(guid);

		if (!instance)
		{
			if (!IsMissionClient())
				return NULL;

			instance = new CF_Permission_Player(NULL);
			Players.Insert(guid, instance);
		}

		instance.OnRecieve(ctx);

		if (IsMissionClient())
		{
			if (m_ClientGUID == guid)
				g_cf_ModuleManager.OnClientPermissionsUpdated();

			instance.PlayerObject = playerUpdatePlayer;
		}

		return instance;
	}

	override CF_Permission_Role CreateRole(string name, ref array<string> data)
	{
		if (Assert_Null(Players))
			return null;

		ref CF_Permission_Role role = new CF_Permission_Role(name);

		role.SerializedData.Copy(data);
		role.Deserialize();

		role.Save();

		Roles.Insert(name, role);

		return role;
	}

	bool LoadRole(string name, out CF_Permission_Role role)
	{
		Assert_Null(Roles);

		role = GetRole(name);

		if (!role)
		{
			role = new CF_Permission_Role(name);
			Roles.Insert(name, role);

			return false;
		}

		return true;
	}

	protected override void OnInit()
	{
		super.OnInit();

		if (Assert_Null(Roles))
			return;

		string sName = "";
		FileAttr oFileAttr = FileAttr.INVALID;
		FindFileHandle oFileHandle = FindFile(__Constants.DIR_ROLES + "*" + __Constants.EXT_ROLE, sName, oFileAttr, FindFileFlags.ALL);

		if (sName != "")
		{
			if (IsValidFolderForRoles(sName, oFileAttr))
				LoadRoleFromFile(sName.Substring(0, sName.Length() - 4));

			while (FindNextFile(oFileHandle, sName, oFileAttr))
				if (IsValidFolderForRoles(sName, oFileAttr))
					LoadRoleFromFile(sName.Substring(0, sName.Length() - 4));
		}
	}

	private void LoadRoleFromFile(string name)
	{
		ref CF_Permission_Role role = new CF_Permission_Role(name);

		if (role.Load())
			Roles.Insert(name, role);
	}

	//TODO: URGENT: READ COTModule.c LINE 270 TODO! 
};