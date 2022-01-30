class CF_EventPlayerArgs : CF_EventArgs
{
	PlayerBase Player;
	PlayerIdentity Identity;

	void CF_EventPlayerArgs(PlayerBase player = null, PlayerIdentity identity = null)
	{
		Player = player;
		Identity = identity;
	}
};

class CF_EventPlayerDisconnectedArgs : CF_EventPlayerArgs
{
	string UID;
	int LogoutTime = -1; // -1 for Disconnected
	bool AuthFailed;
};

class CF_EventNewPlayerArgs : CF_EventPlayerArgs
{
	vector Position;
	ParamsReadContext Context;

	void CF_EventNewPlayerArgs(PlayerBase player = null, PlayerIdentity identity = null, vector position = "0 0 0", ParamsReadContext ctx = null)
	{
		Position = position;
		Context = ctx;
	}
};

class CF_EventPlayerPrepareArgs : CF_EventArgs
{
	PlayerIdentity Identity;
	bool UseDatabase;
	vector Position;
	float Yaw;
	int PreloadTimeout;
};
