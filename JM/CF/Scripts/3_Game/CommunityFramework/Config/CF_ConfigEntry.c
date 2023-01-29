class CF_ConfigEntry
{
	protected ref array<ref CF_ConfigEntry> _entries;
	protected ref CF_ConfigEntry _parent;

	protected string _name;

	void CF_ConfigEntry()
	{
		_entries = new array<ref CF_ConfigEntry>();
	}

	string GetType()
	{
		return "ENTRY";
	}

	string GetName()
	{
		return _name;
	}

	CF_ConfigEntry GetParent()
	{
		return _parent;
	}

	CF_ConfigClass GetClass()
	{
		return null;
	}

	bool IsValue()
	{
		return false;
	}

	bool IsClass()
	{
		return true;
	}

	bool IsClassDecl()
	{
		return true;
	}

	bool IsDelete()
	{
		return true;
	}

	bool IsText()
	{
		return false;
	}

	string GetText()
	{
		return "";
	}

	void SetText(string value)
	{
	}

	bool IsFloat()
	{
		return false;
	}

	float GetFloat()
	{
		return 0;
	}

	void SetFloat(float value)
	{
	}

	bool IsInt()
	{
		return false;
	}

	int GetInt()
	{
		return 0;
	}

	void SetInt(int value)
	{
	}

	bool IsLong()
	{
		return false;
	}

	int GetLong()
	{
		return 0;
	}

	void SetLong(int value)
	{
	}

	CF_ConfigArray GetArray()
	{
		return null;
	}

	bool IsArrayParam()
	{
		return false;
	}

	bool IsArray()
	{
		return false;
	}

	int Count()
	{
		return _entries.Count();
	}

	CF_ConfigEntry Get(int i)
	{
		return _entries[i];
	}

	int FindIndex(string name, bool isClass = false)
	{
		for (int i = 0; i <_entries.Count(); i++)
		{
			if (isClass && !_entries[i].IsClass())
				continue;

			if (_entries[i]._name == name)
				return i;
		}

		return -1;
	}

	bool Parse(CF_Lexer lexer, CF_ConfigClass root)
	{
		CF_Log.Error("Not implemented.");
		return false;
	}

	CF_ConfigEntry Get(string path)
	{
		TStringArray tokens = new TStringArray;
		path.Split(" ", tokens);
		return Get(tokens, 0);
	}

	CF_ConfigEntry Get(TStringArray tokens, int index = 0)
	{
		if (index == tokens.Count())
		{
			return this;
		}

		string lowerToken = "" + tokens[ index ];
		lowerToken.ToLower();
		for (int k = 0; k <_entries.Count(); ++k)
		{
			string nameLower = "" + _entries[k]._name;
			nameLower.ToLower();

			if (lowerToken == nameLower)
			{
				return _entries[k].Get(tokens, index + 1);
			}
		}

		if (IsClass() && GetClass().GetBase() != null)
		{
			return GetClass().GetBase().Get(tokens, index);
		}

		return null;
	}

	CF_TypeConverterBase GetConverter()
	{
		if (IsValue() || (IsArrayParam() && !IsArray()))
		{
			const string variableName = "_value";
			auto converter = CF_TypeConverter.Get(this, variableName);
			if (converter.Read(this, variableName))
			{
				return converter;
			}
		}

		return null;
	}

	CF_TypeConverterBase GetConverter(string path)
	{
		auto cfg = Get(path);
		if (!cfg)
		{
			return null;
		}

		return cfg.GetConverter();
	}

	CF_TypeConverterBase GetConverter(int index)
	{
		auto cfg = Get(index);
		if (!cfg)
		{
			return null;
		}

		return cfg.GetConverter();
	}

	bool AddEntry(CF_ConfigEntry entry)
	{
		return false;
	}
};
