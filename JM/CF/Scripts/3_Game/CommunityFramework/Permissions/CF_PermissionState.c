class CF_PermissionState
{
	int m_Hash;
	int m_State;

	ref map<int, ref CF_PermissionState> m_ChildrenMap;
	ref array<CF_PermissionState> m_Children;

	void CF_PermissionState(int hash, CF_PermissionState parent)
	{
		m_ChildrenMap = new map<int, ref CF_PermissionState>();
		m_Children = new array<CF_PermissionState>();

		if (parent)
		{
			parent.m_ChildrenMap.Insert(hash, this);
			parent.m_Children.Insert(this);
		}
	}

	CF_PermissionState Get(int hash)
	{
		if (hash == 0) return null;

		CF_PermissionState permission;
		if (m_ChildrenMap.Find(hash, permission)) return permission;

		return new CF_PermissionState(hash, this);
	}
	
	void NetworkWrite(ParamsWriteContext ctx)
	{
		ctx.Write(m_Children.Count());

		for (int i = 0; i < m_Children.Count(); i++)
		{
			ctx.Write(m_Children[i].m_Hash);
			ctx.Write(m_Children[i].m_State);

			m_Children[i].NetworkWrite(ctx);
		}
	}

	bool NetworkRead(ParamsReadContext ctx)
	{
		int count;
		ctx.Read(count);

		for (int i = 0; i < count; i++)
		{
			int hash;
			ctx.Read(hash);

			CF_PermissionState permission;
			if (!m_ChildrenMap.Find(hash, permission))
			{
				permission = new CF_PermissionState(hash, this);
			}

			ctx.Read(permission.m_State);

			permission.NetworkRead(ctx);
		}

		return true;
	}
};

class CF_Player : Managed
{
	ref CF_PermissionState m_Root = new CF_PermissionState("root".Hash(), null);
};
