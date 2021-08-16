class CF_PermissionHashItem
{
	ref CF_PermissionHashItem m_Next;

	int m_Value;

	void CF_PermissionHashItem(int value, CF_PermissionHashItem parent = null)
	{
		m_Value = value;

		if (parent) parent.m_Next = this;
	}
};
