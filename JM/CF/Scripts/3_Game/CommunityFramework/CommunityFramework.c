static bool IsMissionHost()
{
	if ( !GetGame() )
		return false;

    return GetGame().IsServer() || !GetGame().IsMultiplayer();
}

static bool IsMissionClient()
{
	if ( !GetGame() )
		return false;

    return GetGame().IsClient() || !GetGame().IsMultiplayer();
}