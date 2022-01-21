class ConfigArray : ConfigEntry
{
	override string GetType()
	{
		return "ARRAY";
	}

	override bool IsArray()
	{
		return true;
	}

	override ConfigArray GetArray()
	{
		return this;
	}

	override bool Parse( ConfigReader reader, ConfigFile file )
	{
		string c = reader.SkipWhitespace();

		if ( c != "{" )
		{
			reader.Error( "'" + c + "' encountered instead of '{'" );
			return false;
		}

		for ( int vpp = 0; vpp < 100; vpp++ )
		{
			c = reader.SkipWhitespace();

			reader.BackChar();

			ConfigArrayParam entry = NULL;

			if ( c == "{" )
			{
				entry = new ConfigArrayParamArray();
				entry._parent = this;
				if ( !entry.Parse( reader, file ) )
					return false;
			} else
			{
				bool quoted;
				string value = reader.GetQuotedWord( quoted );

				if ( value.Length() > 0 )
				{
					if ( quoted )
					{
						entry = new ConfigArrayParamText();
						entry._parent = this;
						entry.SetText( value );
					} else
					{
						if ( value.Contains( "." ) )
						{
							entry = new ConfigArrayParamFloat();
							entry.SetFloat( value.ToFloat() );
							entry._parent = this;
						} else
						{
							entry = new ConfigArrayParamInt();
							entry.SetInt( value.ToInt() );
							entry._parent = this;
						}
					}
				}
			}

			if ( entry )
				_entries.Insert( entry );
			
			c = reader.SkipWhitespace();

			if ( c == "}" )
				return true;

			if ( c != "," && c != ";" )
			{
				reader.Error( "'" + c + "' encounted instead of ','" );
				return false;
			}
		}

		reader.Error( "Prematurely ending the array reading, going for too long." );
		return false;
	}
};