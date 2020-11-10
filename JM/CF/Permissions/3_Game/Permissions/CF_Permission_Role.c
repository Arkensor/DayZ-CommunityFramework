typedef CF_Permission_Role JMRole;

class CF_Permission_Role : Managed
{
	ref CF_Permission_Node RootPermission;

	string Name;

	ref array<string> SerializedData;

	void CF_Permission_Role(string name)
	{
		Name = name;

		RootPermission = new CF_Permission_Node(__Constants.PERM_ROOT);

		SerializedData = new array<string>;
	}

	void ~CF_Permission_Role()
	{
		delete RootPermission;

		delete SerializedData;
	}

	void CopyPermissions(ref CF_Permission_Node copy)
	{
		ref array<string> data = new array<string>;
		copy.Serialize(data);

		for (int i = 0; i < data.Count(); i++)
		{
			AddPermission(data[i]);
		}
	}

	void ClearPermissions()
	{
		delete RootPermission;

		RootPermission = new CF_Permission_Node(__Constants.PERM_ROOT);
	}

	void AddPermission(string permission, CF_Permission_Type type = CF_Permission_Type.INHERIT)
	{
		RootPermission.AddPermission(permission, type);
	}

	bool HasPermission(string permission, out CF_Permission_Type permType)
	{
		return RootPermission.HasPermission(permission, permType);
	}

	ref array<string> Serialize()
	{
		SerializedData.Clear();

		RootPermission.Serialize(SerializedData);

		return SerializedData;
	}

	void Deserialize()
	{
		for (int i = 0; i < SerializedData.Count(); i++)
		{
			AddPermission(SerializedData[i]);
		}
	}

	string FileReadyStripName(string name)
	{
		name.Replace("\\", "");
		name.Replace("/", "");
		name.Replace("=", "");
		name.Replace("+", "");

		return name;
	}

	bool Save()
	{
		string filename = FileReadyStripName(Name);

		FileHandle file = OpenFile(__Constants.DIR_ROLES + filename + __Constants.EXT_ROLE, FileMode.WRITE);

		Serialize();

		if (file != 0)
		{
			string line;

			for (int i = 0; i < SerializedData.Count(); i++)
			{
				FPrintln(file, SerializedData[i]);
			}

			CloseFile(file);

			return true;
		}
		else
		{
			return false;
		}
	}

	bool Load()
	{
		string filename = FileReadyStripName(Name);
		FileHandle file = OpenFile(__Constants.DIR_ROLES + filename + __Constants.EXT_ROLE, FileMode.READ);

		ref array<string> data = new array<string>;

		if (file != 0)
		{
			string line;

			while (FGets(file, line) > 0)
			{
				data.Insert(line);
			}

			CloseFile(file);

			for (int i = 0; i < data.Count(); i++)
			{
				AddPermission(data[i]);
			}

			Serialize();
		}
		else
		{
			return false;
		}

		return true;
	}

	void DebugPrint()
	{
		RootPermission.DebugPrint(0);
	}
}