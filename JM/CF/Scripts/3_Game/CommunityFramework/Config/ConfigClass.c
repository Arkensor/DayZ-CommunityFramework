class ConfigClassDeclaration : ConfigClass
{
	override bool IsClassDecl()
	{
		return true;
	}
};

class ConfigDelete : ConfigEntry
{
	override bool IsDelete()
	{
		return true;
	}
};

class ConfigClass : ConfigEntry
{
	private ConfigClass _base;

	void ConfigClass()
	{

	}

	override string GetType()
	{
		return "CLASS";
	}

	override ConfigClass GetClass()
	{
		return this;
	}

	ConfigClass GetBase()
	{
		return _base;
	}

	private ConfigClass SetBase( string name )
	{
		int baseIndex = _parent.FindIndex( name );
		int thisIndex = _parent.FindIndex( _name );
		if ( baseIndex >= 0 && ( baseIndex < thisIndex || thisIndex < 0 ) )
		{
			return _parent._entries[ baseIndex ].GetClass();
		}

		ConfigEntry possibleEntry = NULL;

		if ( _parent.GetClass()._base != NULL )
		{
			possibleEntry = _parent.GetClass()._base.Find( name, true, true );
		}

		if ( possibleEntry == NULL && _parent._parent != NULL )
		{
			possibleEntry = _parent._parent.GetClass().Find( name, true, true );
		}

		if ( possibleEntry != NULL && possibleEntry.IsClass() )
		{
			return possibleEntry.GetClass();
		}

		return NULL;
	}

	ConfigEntry Find( string name, bool checkParent, bool checkBase )
	{
		int idx = FindIndex( name, true );
		if ( idx >= 0 )
			return _entries[idx];

		ConfigEntry entry = NULL;

		if ( checkBase && _base != NULL )
		{
			entry = _base.Find( name, true, true );
			if ( entry != NULL )
				return entry;
		}

		if ( checkParent && _parent != NULL && _parent.GetClass() != NULL )
		{
			entry = _parent.GetClass().Find( name, true, checkBase );
			if ( entry != NULL )
				return entry;
		}

		return NULL;
	}

	override bool Parse( ConfigReader reader, ConfigFile file )
	{
		for ( int vpp = 0; vpp < 100; vpp++ )
		{
			string c = reader.SkipWhitespace();

			if ( reader.EOF() )
			{
				if ( this == file )
					return true;

				reader.Error( "Unexpected EOF reached." );
				return false;
			}

			if ( c == "#" )
			{
				reader.NextLine();
			} else if (c == "}" )
			{
				c = reader.GetCharacter();
				while ( reader.IsWhitespace( c ) || c == ";" )
					c = reader.GetCharacter();

				reader.BackChar();
				return true;
			}

			reader.BackChar();

			ConfigEntry entry = NULL;
			string name = "";

			string token = reader.GetWord();
			if ( token == "delete" )
			{
				name = reader.GetWord();

				c = reader.SkipWhitespace();

				if ( c == ";" )
				{
					entry = new ConfigDelete();
					entry._name = name;
					entry._parent = this;
				} else
				{
					reader.Error( "'" + c + "' encountered instead of ';'" );
					return false;
				}
			} else if ( token == "class" )
			{
				name = reader.GetWord();

				c = reader.SkipWhitespace();

				if ( c == ";" )
				{
					entry = new ConfigClassDeclaration();
					entry._name = name;
					entry._parent = this;
				} else
				{
					entry = new ConfigClass();
					entry._name = name;
					entry._parent = this;

					if ( c == ":" )
					{
						string baseName = reader.GetWord();
						ConfigEntry baseEntry = Find( baseName, true, true );
						if ( baseEntry == NULL )
						{
							reader.Error( "Undefined base class '" + baseName + "'" );
							return false;
						}

						if ( !baseEntry.IsClass() )
						{
							reader.Error( "'" + baseName + "' is not a class" );
							return false;
						}

						entry.GetClass()._base = baseEntry.GetClass();
						c = reader.GetCharacter();
					}

					while ( c != "{" )
					{
						if ( !reader.IsWhitespace(c) )
						{
							reader.Error( "'" + c + "' encountered instead of '{'");
							return false;
						}

						c = reader.GetCharacter();
					}

					if ( !entry.Parse( reader, file ) )
						return false;
				}
			} else if ( token == "enum" )
			{
				reader.Error( "Enum is not supported");
				return false;
			} else if ( token != "" )
			{
				c = reader.GetCharacter();
				name = token;

				if ( c == "[" )
				{
					c = reader.SkipWhitespace();

					if (c != "]")
					{
						reader.Error( "'" + c + "' encountered instead of ']'" );
						return false;
					}

					c = reader.SkipWhitespace();

					if (c != "=")
					{
						reader.Error( "'" + c + "' encountered instead of '='" );
						return false;
					}

					entry = new ConfigArray();
					entry._name = name;
					entry._parent = this;
					if ( !entry.Parse( reader, file ) )
						return false;

					c = reader.SkipWhitespace();

					if ( c != ";")
					{
						reader.Error( "'" + c + "' encountered instead of ';'" );
						return false;
					}
				} else
				{
					while ( reader.IsWhitespace( c ) )
						c = reader.GetCharacter();

					if ( c != "=" )
					{
						reader.Error( "'" + c + "' encountered instead of '='" );
						return false;
					}

					bool quoted;
					string value = reader.GetQuotedWord( quoted );

					c = reader.SkipWhitespace();

					if (c == "}" )
					{
						reader.Warning( "'" + c + "' encountered instead of ';'" );
						reader.BackChar();
					} else if (c != ";" )
					{
						reader.Error( "Missing ';' at the end of the line" );
						return false;

						// TODO: resolve
						/*
						if (c != '\n' && c != '\r')
						{
							if (!quoted)
							{
								ParseError(input, $"'{(char)c}' encountered instead of ';'");
								return false;
							}
							input.BackChar()
						}
						ParseWarning(input, $"Missing ';' at the end of the line");
						*/
					}

					if ( quoted )
					{
						entry = new ConfigValueText();
						entry._name = name;
						entry.SetText( value );
						entry._parent = this;
					} else
					{
						if ( value.Contains( "." ) )
						{
							entry = new ConfigValueFloat();
							entry._name = name;
							entry.SetFloat( value.ToFloat() );
							entry._parent = this;
						} else
						{
							entry = new ConfigValueInt();
							entry._name = name;
							entry.SetInt( value.ToInt() );
							entry._parent = this;
						}
					}
				}
			}

			if ( entry != NULL )
			{
				int idx = FindIndex( entry._name );
				if ( idx < 0)
				{
					_entries.Insert( entry );
				} else
				{
					reader.Error( "'" + entry._name + "' already defined" );
				}
			}
		}

		reader.Error( "Prematurely ending the class reading, going for too long." );
		return false;
	}
};