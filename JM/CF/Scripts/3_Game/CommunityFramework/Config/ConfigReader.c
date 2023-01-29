class ConfigReader : Managed
{	
	private int _arrIdx = 0;
	private int _bufIdx = -1;

	private ref array< string > _lines = new array< string >;

	private void ConfigReader()
	{ 
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
	}

	void ~ConfigReader()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
	}

	static ConfigReader Open( string path )
	{
		ConfigReader reader = new ConfigReader();

		FileHandle fileHandle = OpenFile( path, FileMode.READ );

		string lineContent;
		while ( FGets( fileHandle, lineContent ) >= 0 )
		{
			if ( lineContent.Length() != 0 )
			{
				reader._lines.Insert( lineContent );
			}
		}

		CloseFile( fileHandle );

		return reader;
	}

	string BackChar()
	{
		_bufIdx--;
		if ( _bufIdx < 0 )
		{
			if ( !PreviousLine() )
			{
				return "";
			}
		}

		return _lines[_arrIdx].Substring( _bufIdx, 1 );
	}

	private string ReadChar()
	{
		_bufIdx++;

		if ( _bufIdx >= _lines[_arrIdx].Length() )
		{
			if ( !NextLine() )
			{
				return "";
			}
		}

		return _lines[_arrIdx].Substring( _bufIdx, 1 );
	}

	bool NextLine()
	{
		_bufIdx = 0;

		_arrIdx++;

		while ( _arrIdx < _lines.Count() )
		{
			if ( _lines[_arrIdx].Length() <= 0 )
				_arrIdx++;
			else
				return true;
		}

		return false;
	}

	bool PreviousLine()
	{
		_arrIdx--;

		while ( _arrIdx >= 0 )
		{
			if ( _lines[_arrIdx].Length() <= 0 )
				_arrIdx--;
			else
			{
				_bufIdx = _lines[_arrIdx].Length() - 1;
				return true;
			}
		}

		return false;
	}

	bool EOF()
	{
		return _arrIdx >= _lines.Count() || ( _arrIdx == _lines.Count() - 1 && _bufIdx >= _lines[_arrIdx].Length() );
	}

	private void SkipComment()
	{
		string c = ReadChar();
		while ( true  )
		{
			if ( EOF() )
			{
				CF_Log.Error( "Unexpected end of file while parsing XML comment!" );
				break;
			}

			if ( c != "*" )
			{
				c = ReadChar();
				continue;
			}

			BackChar();

			string check = ReadChar();
			if ( check == "/" )
			{
				return;
			} else
			{
				c = ReadChar();
			}
		}
	}

	string GetCharacter()
	{		
		string c = ReadChar();
		while ( true )
		{
			if ( c == "/" )
			{
				c = ReadChar();
				if ( c == "/" )
				{
					NextLine();
				} else if ( c == "*" )
				{
					SkipComment();
				} else
				{
					BackChar();
					return c;
				}
			} else
			{
				return c;
			}

			c = ReadChar();
		}

		return c;
	}

	bool IsWhitespace( string c )
	{
		if ( c == " " )
			return true;
		if ( c == "\t" )
			return true;
		if ( c == "\n" )
			return true;
		if ( c == "\r" )
			return true;

		//if ( c == "" )
		//	Error( "Unexpected end of string" );

		return false;
	}

	bool IsLetterOrDigit( string c )
	{
		return IsLetterOrDigit( c, false );
	}

	bool IsLetterOrDigit( string c, bool isQuoted )
	{
		int i = _cf_characters.Find( c );
		if ( i == -1 )
		{
			return false;
		}

		if ( isQuoted )
		{
			return i >= 32 && i <= 126;
		}
			
		if ( i >= 48 && i <= 57 )
		{
			return true;
		}

		if ( i > 90 )
			i -= 32;

		if ( i >= 65 && i <= 90 )
		{
			return true;
		}

		return false;
	}

	string SkipWhitespace()
	{
		string c = GetCharacter();
		while ( IsWhitespace( c ) )
			c = GetCharacter();

		return c;
	}

	string GetWord()
	{
		string word = "";
		
		string c = SkipWhitespace();

		while ( IsLetterOrDigit( c ) )
		{
			word = word + c;
			c = GetCharacter();
		}

		BackChar();

		return word;
	}

	string GetQuotedWord( out bool isQuoted )
	{
		string word = "";
		
		string c = SkipWhitespace();

		if ( c == "\"" )
		{
			c = "";
			isQuoted = true;
		} else
		{
			isQuoted = false;
		}

		while ( ( IsLetterOrDigit( c, isQuoted ) || c == "" ) && !EOF() )
		{
			word = word + c;
			c = GetCharacter();
			if ( isQuoted && c == "\"" )
			{
				return word;
			}
		}

		BackChar();

		return word;
	}

	void Error( string msg )
	{
		CF_Log.Error( "[" + ( _arrIdx + 1 ) + ":" + _bufIdx + "] " + msg );
	}

	void Warning( string msg )
	{
		CF_Log.Warn( "[" + ( _arrIdx + 1 ) + ":" + _bufIdx + "] " + msg );
	}
};