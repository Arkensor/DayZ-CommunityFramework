modded class MissionGameplay
{
	protected CF_Permission_PlayerBase m_Permission_OfflinePlayer;

	void MissionGameplay()
	{
		if (IsMissionOffline() && g_Game.GetGameState() != DayZGameState.MAIN_MENU)
		{
			if (CF.Permission.OnClientConnected(null, m_Permission_OfflinePlayer))
			{
				//GetCommunityOnlineToolsBase().SetClient(m_Permission_OfflinePlayer);
			}
		}
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		if (IsMissionOffline())
		{
			CF.Permission.OnClientDisconnected(CF.Permission.OFFLINE_GUID, m_Permission_OfflinePlayer);
		}
	}
};