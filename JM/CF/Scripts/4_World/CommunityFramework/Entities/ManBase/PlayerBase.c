#ifdef CF_MODSTORAGE
modded class PlayerBase
{
	protected static ref TStringArray s_CF_QueuedIdentityIDs = new TStringArray();
	protected string m_CF_QueuedIdentityID;

	static void CF_QueueIdentityId(string id)
	{
		s_CF_QueuedIdentityIDs.Insert(id);
	}

	static string CF_DequeueIdentityId()
	{
		string id = s_CF_QueuedIdentityIDs[0];
		s_CF_QueuedIdentityIDs.RemoveOrdered(0);
		return id;
	}

	string CF_GetQueuedIdentityId()
	{
		if (!m_CF_QueuedIdentityID)
		{
			m_CF_QueuedIdentityID = CF_DequeueIdentityId();
		}

		return m_CF_QueuedIdentityID;
	}
};
#endif
