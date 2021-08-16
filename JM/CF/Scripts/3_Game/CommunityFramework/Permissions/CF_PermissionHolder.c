class CF_PermissionHolder
{
	string m_ID;

	ref CF_PermissionState m_States = new CF_PermissionState(0, null);

	void SetState(CF_PermissionHashItem hashes, int state)
	{
		CF_PermissionState permission = m_States;

		while (hashes && permission)
		{
			permission = permission[hashes.m_Value];
		}

		if (!permission) return;

		permission.m_State = state;
	}

	bool HasPermission(CF_PermissionHashItem hashes)
	{
		CF_PermissionState permission = m_States;

		int lastState = 0;
		while (hashes && permission)
		{
			if (permission.m_State != 2) lastState = permission.m_State;

			permission = permission[hashes.m_Value];
		}

		return lastState;
	}
};
