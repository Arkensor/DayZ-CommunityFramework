class ConfigEntry : Managed
{
	protected ref array< ref ConfigEntry > _entries;

	protected ref ConfigEntry _parent;

	protected string _name;

	void ConfigEntry()
	{
		_entries = new array< ref ConfigEntry >();

		_parent = NULL;

		_name = "";
	}

	string GetType()
	{
		return "ENTRY";
	}

	string GetName()
	{
		return _name;
	}

	ConfigEntry GetParent()
	{
		return _parent;
	}

	ConfigClass GetClass()
	{
		return NULL;
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

	void SetText( string value )
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

	void SetFloat( float value )
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

	void SetInt( int value )
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

	void SetLong( int value )
	{
	}

	ConfigArray GetArray()
	{
		return NULL;
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

	ConfigEntry Get( int i )
	{
		return _entries[i];
	}

	int FindIndex( string name, bool isClass = false )
	{
		for ( int i = 0; i < _entries.Count(); i++ )
		{
			if ( isClass && !_entries[i].IsClass() )
				continue;

			if ( _entries[i]._name == name )
				return i;
		}

		return -1;
	}

	bool Parse( ConfigReader reader, ConfigFile file )
	{
		CF_Log.Error( "Not implemented." );
		return false;
	}

	ConfigEntry Get( string path )
	{
		TStringArray tokens = new TStringArray;
		path.Split( " ", tokens );
		return Get( tokens, 0 );
	}

	ConfigEntry Get( TStringArray tokens, int index = 0 )
	{
		string lowerToken = "" + tokens[ index ];
		lowerToken.ToLower();
		for ( int k = 0; k < _entries.Count(); ++k )
		{
			string nameLower = "" + _entries[k]._name;
			nameLower.ToLower();

			if ( lowerToken == nameLower )
			{
				if ( index + 1 >= tokens.Count() )
				{
					return _entries[k];
				}

				return _entries[k].Get( tokens, index + 1 );
			}
		}

		if ( IsClass() && GetClass().GetBase() != NULL )
		{
			return GetClass().GetBase().Get( tokens, index );
		}

		return NULL;
	}
};
