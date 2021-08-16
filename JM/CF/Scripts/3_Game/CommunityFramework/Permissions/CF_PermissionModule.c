class CF_PermissionModule : CF_Module
{
	static CF_PermissionModule s_PM_Instance;

	ref CF_Permission m_Root = new CF_Permission("root", null);

	ref map<string, ref CF_PermissionHolder> m_Holders = new map<string, ref CF_PermissionHolder>();



	static void GenerateHash(string permission, out array<int> hash)
	{

	}

	static bool HasPermission(string id)
	{

	}
};
