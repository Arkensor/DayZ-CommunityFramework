class CF_Permission_PlayerFile : Managed
{
	[NonSerialized()]
	string m_FileName;

	ref array<string> Roles;

	void CF_Permission_PlayerFile()
	{
		Roles = new array<string>;
	}

	void ~CF_Permission_PlayerFile()
	{
		delete Roles;
	}

	static string FileReadyStripName(string name)
	{
		name.Replace("\\", "");
		name.Replace("/", "");
		name.Replace("=", "");
		name.Replace("+", "");

		return name;
	}

	static bool Load(CF_Permission_PlayerBase inst, inout CF_Permission_PlayerFile playerFile)
	{
		playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER;
		if (FileExist(playerFile.m_FileName))
		{
			JsonFileLoader<CF_Permission_PlayerFile>.JsonLoadFile(playerFile.m_FileName, playerFile);

			playerFile.Save();
			return true;
		}

		playerFile.m_FileName = CF.Permission.DIR_PLAYERS + inst.GetSteam64ID() + CF.Permission.EXT_PLAYER;
		if (FileExist(playerFile.m_FileName))
		{
			JsonFileLoader<CF_Permission_PlayerFile>.JsonLoadFile(playerFile.m_FileName, playerFile);

			DeleteFile(playerFile.m_FileName);
			playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER;

			playerFile.Save();
			return true;
		}

		playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER + CF.Permission.EXT_WINDOWS_DEFAULT;
		if (FileExist(playerFile.m_FileName))
		{
			JsonFileLoader<CF_Permission_PlayerFile>.JsonLoadFile(playerFile.m_FileName, playerFile);

			DeleteFile(playerFile.m_FileName);
			playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER;

			playerFile.Save();
			return true;
		}

		playerFile.m_FileName = CF.Permission.DIR_PLAYERS + inst.GetSteam64ID() + CF.Permission.EXT_PLAYER + CF.Permission.EXT_WINDOWS_DEFAULT;
		if (FileExist(playerFile.m_FileName))
		{
			JsonFileLoader<CF_Permission_PlayerFile>.JsonLoadFile(playerFile.m_FileName, playerFile);

			DeleteFile(playerFile.m_FileName);
			playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER;

			playerFile.Save();
			return true;
		}

		playerFile.m_FileName = CF.Permission.DIR_PLAYERS + FileReadyStripName(inst.GetGUID()) + CF.Permission.EXT_PLAYER;
		playerFile.Roles.Insert("everyone");
		return false;
	}

	void Save()
	{
		JsonFileLoader<CF_Permission_PlayerFile>.JsonSaveFile(m_FileName, this);
	}
};