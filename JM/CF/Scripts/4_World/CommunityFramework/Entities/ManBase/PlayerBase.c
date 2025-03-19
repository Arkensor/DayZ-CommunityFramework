modded class PlayerBase
{
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
		}
		else
		{
			CF_Log.Warn("[CF] PlayerBase::OnSelectPlayer - Player without identity has been selected");  //! Shouldn't be possible to happen
		}
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

		return m_CF_IdentityID;
	}

	override bool OnStoreLoadLifespan(ParamsReadContext ctx, int version)
	{
		int lifespan_state = 0;
		if (!ctx.Read(lifespan_state))
			return false;

		//! Attempt fix if player is not in modstorageplayers.bin, but read data indicates it has been saved before with CF loaded
		//! It is still unclear why this can happen
		if (lifespan_state > LifeSpanState.COUNT - 1)
		{
			CF_Log.Warn("[CF] Lifespan state " + lifespan_state + " exceeds valid range " + (LifeSpanState.COUNT - 1));

			if (lifespan_state <= CF_ModStorage.VERSION && !m_CF_ModStorage.m_Module.IsEntity(this))
			{
				int cf_version = lifespan_state;
				CF_Log.Warn("[CF] Assuming CF ModStorage version " + cf_version);

				if (!m_CF_ModStorage.OnStoreLoad_CF(ctx, cf_version))
					return false;

				m_CF_ModStorage.m_Module.AddEntity(this);

				return super.OnStoreLoadLifespan(ctx, version);
			}
		}

		m_LifeSpanState = lifespan_state;
		
		int last_shaved = 0;
		if (!ctx.Read(last_shaved))
			return false;
		m_LastShavedSeconds = last_shaved;
		
		if (version < 122)
		{
			bool bloody_hands_old;
			if (!ctx.Read(bloody_hands_old))
			return false;
			m_HasBloodyHandsVisible = bloody_hands_old;
		}
		else
		{
			int bloody_hands = 0;
			if (!ctx.Read(bloody_hands))
				return false;
			m_HasBloodyHandsVisible = bloody_hands;
		}
		
		
		bool blood_visible = false;
		if (!ctx.Read(blood_visible))
			return false;
		m_HasBloodTypeVisible = blood_visible;
		
		int blood_type = 0;
		if (!ctx.Read(blood_type))
			return false;
		m_BloodType = blood_type;

		return true;
	}
};
