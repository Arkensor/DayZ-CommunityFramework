modded class PlayerBase
{
	protected static ref TStringArray s_CF_QueuedIdentityIDs = new TStringArray();
	protected string m_CF_IdentityID;

	override void OnSelectPlayer()
	{
#ifdef DIAG_DEVELOPER
		PrintFormat(GetGame().GetTickTime().ToString() + " [CF] OnSelectPlayer");
#endif

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
					CF_LogWarn("OnSelectPlayer - Previously set identity ID %1 doesn't match current ID %2 for player %3", m_CF_IdentityID, id, ToString());  //! Shouldn't be possible to happen
				CF_Log.Info("OnSelectPlayer - using ID %1", id);
				m_CF_IdentityID = id;
			}
			s_CF_QueuedIdentityIDs.RemoveItem(id);
		}
		else
		{
			CF_Log.Error("OnSelectPlayer - Player without identity has been selected");  //! Shouldn't be possible to happen
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
					CF_LogWarn("CF_GetIdentityId - Previously set identity ID %1 doesn't match current ID %2 for player %3", m_CF_IdentityID, id, ToString());  //! Shouldn't be possible to happen
				CF_Log.Info("CF_GetIdentityId - using ID %1", id);
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
						CF_LogWarn("CF_GetIdentityId - using queued ID %1", id);
						m_CF_IdentityID = id;
						return m_CF_IdentityID;
					}
				}
				CF_LogWarn("CF_GetIdentityId - discarded queued ID %1", id);
			}
			CF_LogWarn("CF_GetIdentityId - discarded %1 queued IDs", count.ToString());
		}

		return m_CF_IdentityID;
	}

	/**
	 * @brief forced warning irrespective of log level
	 */
	void CF_LogWarn(string message, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "")
	{
		int logLevel = CF_Log.Level;
		CF_Log.Level = CF_LogLevel.WARNING;
		CF_Log.Warn(message, param1, param2, param3, param4, param5, param6, param7, param8, param9);
		CF_Log.Level = logLevel;
	}
};
