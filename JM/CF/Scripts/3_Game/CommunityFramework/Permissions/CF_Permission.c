class CF_Permission
{
	string m_Name;
	int m_Hash;

	CF_Permission m_Parent;
	ref map<int, ref CF_Permission> m_Children;

	void CF_Permission(string name, CF_Permission parent, int hash = 0)
	{
		m_Name = name;
		m_Hash = hash;
		if (m_Hash == 0) m_Hash = m_Name.Hash();

		m_Parent = parent;
		m_Children = new map<int, ref CF_Permission>();

		if (m_Parent)
		{
			m_Parent.m_Children.Insert(m_Hash, this);
		}
	}

	CF_Permission Get(string name)
	{
		return Get(name, name.Hash());
	}

	CF_Permission Get(int hash)
	{
		return Get("", hash);
	}

	CF_Permission Get(string name, int hash)
	{
		if (hash == 0) return null;

		CF_Permission permission;
		if (m_Children.Find(hash, permission)) return permission;

		return new CF_Permission(name, this, hash);
	}

	void SetState(CF_PermissionState root, int state)
	{
		array<int> hashes = new array<int>();

		CF_Permission permission = this;
		while (permission)
		{
			hashes.Insert(permission.m_Hash);
			permission = permission.m_Parent;
		}

		for (int i = hashes.Count() - 1; i >= 0; i--)
		{
			root = root.Get(hashes[i]);
			if (!root) return;
		}

		root.m_State = state;
	}

	int GetState(CF_PermissionState root)
	{
		array<int> hashes = new array<int>();

		CF_Permission permission = this;
		while (permission)
		{
			hashes.Insert(permission.m_Hash);
			permission = permission.m_Parent;
		}

		for (int i = hashes.Count() - 1; i >= 0; i--)
		{
			root = root.Get(hashes[i]);
			if (!root) return 0;
		}

		return root.m_State;
	}

	bool Has(CF_PermissionState root)
	{
		array<int> hashes = new array<int>();

		CF_Permission permission = this;
		while (permission)
		{
			hashes.Insert(permission.m_Hash);
			permission = permission.m_Parent;
		}

		int lastState = 0;

		for (int i = hashes.Count() - 1; i >= 0; i--)
		{
			root = root.Get(hashes[i]);

			if (root.m_State != 2) lastState = root.m_State;

			if (!root) return 0;
		}

		return lastState;
	}
};
