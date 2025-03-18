modded class PlayerBase
{
	protected static ref TStringArray s_CF_QueuedIdentityIDs = new TStringArray();
	protected string m_CF_IdentityID;

	override void OnSelectPlayer()
	{
		CF_Log.Debug("[CF] PlayerBase::OnSelectPlayer");

		super.OnSelectPlayer();

		//! Store the identity ID because identity will not be available during save after player has disconnected
		//! (identity will already be removed) and we don't want to use a queued ID at that point
		PlayerIdentity identity = GetIdentity();
		if (identity)
		{
			string id = identity.GetId();
			if (m_CF_IdentityID != id)
			{
				if (m_CF_IdentityID)
					CF_Log.Warn("[CF] PlayerBase::OnSelectPlayer - previously set identity ID %1 doesn't match current ID %2 for player %3", m_CF_IdentityID, id, ToString());  //! Shouldn't be possible to happen
				CF_Log.Debug("[CF] PlayerBase::OnSelectPlayer - using ID %1", id);
				m_CF_IdentityID = id;
			}
			s_CF_QueuedIdentityIDs.RemoveItem(id);
		}
		else
		{
			CF_Log.Warn("[CF] PlayerBase::OnSelectPlayer - Player without identity has been selected");  //! Shouldn't be possible to happen
		}
	}

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

	void CF_SetIdentityId(string id)
	{
		if (CF.IsCallFrom({"PlayerDisconnected"}))
			m_CF_IdentityID = id;
	}

	string CF_GetIdentityId(bool fallBackToQueue=true)
	{
		PlayerIdentity currentIdentity = GetIdentity();
		string id;

		//! Always prefer current identity when it is available
		if (currentIdentity)
		{
			id = currentIdentity.GetId();
			if (m_CF_IdentityID != id)
			{
				if (m_CF_IdentityID)
					CF_Log.Warn("[CF] PlayerBase::CF_GetIdentityId - previously set identity ID %1 doesn't match current ID %2 for player %3", m_CF_IdentityID, id, ToString());  //! Shouldn't be possible to happen
				CF_Log.Debug("[CF] PlayerBase::CF_GetIdentityId - using ID %1", id);
				m_CF_IdentityID = id;
			}
		}
		else if (!m_CF_IdentityID && s_CF_QueuedIdentityIDs.Count() && fallBackToQueue)
		{
			//! TODO: This code path may not actually be used/needed anymore?

			array<PlayerIdentity> identities();
			GetDayZGame().GetPlayerIndentities(identities);
			int count = s_CF_QueuedIdentityIDs.Count();
			while (s_CF_QueuedIdentityIDs.Count())
			{
				id = CF_DequeueIdentityId();
				if (!id) break;
				//! Make sure this is not a stale ID. If it's not in the list,
				//! the player didn't finish connecting (client crash, connection error etc)
				foreach (PlayerIdentity identity: identities)
				{
					if (id == identity.GetId())
					{
						CF_Log.Warn("[CF] PlayerBase::CF_GetIdentityId - using queued ID %1", id);
						m_CF_IdentityID = id;
						return m_CF_IdentityID;
					}
				}
				CF_Log.Warn("[CF] PlayerBase::CF_GetIdentityId - discarded queued ID %1", id);
			}
			CF_Log.Warn("[CF] PlayerBase::CF_GetIdentityId - discarded %1 queued IDs", count.ToString());
		}

		return m_CF_IdentityID;
	}
};
