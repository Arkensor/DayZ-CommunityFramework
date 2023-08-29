typedef CF_XML_Reader XMLReader;

class CF_XML_Reader : Managed
{
	private int _arrIdx = 0;
	private int _bufIdx = -1;

	private bool _wasNewLine;

	private ref array<string> _lines = new array<string>;

	void CF_XML_Reader()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
	}

	void ~CF_XML_Reader()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this);
#endif
	}
	
	void GetPosition(out int arrIdx, out int bufIdx)
	{
		arrIdx = _arrIdx;
		bufIdx = _bufIdx;
	}
	
	void SetPosition(out int arrIdx, out int bufIdx)
	{
		_arrIdx = arrIdx;
		_bufIdx = bufIdx;
	}

	void Err(string message)
	{
		CF_Log.Error("[" + (_arrIdx + 1 ) + ":" + _bufIdx + "] " + message);
	}

	void AddLine(string line)
	{
		if (line.Length() != 0)
			_lines.Insert(line);
	}

	bool WasNewLine()
	{
		return _wasNewLine;
	}

	string BackChar()
	{
		_wasNewLine = false;

		_bufIdx--;
		if (_bufIdx < 0)
		{
			_arrIdx--;

			if (_arrIdx < 0)
			{
				return "";
			}

			_bufIdx = _lines[_arrIdx].Length() - 1;
		}

		if (_bufIdx == 0) _wasNewLine = true;

		return _lines[_arrIdx].SubstringUtf8(_bufIdx, 1);
	}

	private string ReadChar()
	{
		_wasNewLine = false;

		_bufIdx++;

		if (_bufIdx >= _lines[_arrIdx].Length())
		{
			_bufIdx = 0;

			_arrIdx++;

			_wasNewLine = true;

			if (_arrIdx >= _lines.Count())
			{
				return "";
			}
		}

		return _lines[_arrIdx].SubstringUtf8(_bufIdx, 1);
	}

	bool EOF()
	{
		return _arrIdx >= _lines.Count() || (_arrIdx == _lines.Count() - 1 && _bufIdx >= _lines[_arrIdx].Length());
	}

	private void SkipComment()
	{
		string c = ReadChar();
		while (true)
		{
			if (EOF())
			{
				CF_Log.Error("Unexpected end of file while parsing XML comment!");
				break;
			}

			if (c != ">")
			{
				c = ReadChar();
				continue;
			}

			BackChar();
			BackChar();
			BackChar();

			string check = ReadChar() + ReadChar() + ReadChar();
			if (check == "-->")
			{
				return;
			}
			else
			{
				c = ReadChar();
			}
		}
	}

	string GetCharacter()
	{
		string c = ReadChar();
		while (true)
		{
			if (c == "<")
			{
				c = ReadChar();
				if (c == "!")
				{
					c = ReadChar();
					if (c == "-")
					{
						c = ReadChar();
						if (c == "-")
						{
							SkipComment();
						}
						else
						{
							BackChar();
							BackChar();
							BackChar();
							return "<";
						}
					}
					else
					{
						BackChar();
						BackChar();
						return "<";
					}
				}
				else
				{
					BackChar();
					return "<";
				}
			}
			else
			{
				return c;
			}

			c = ReadChar();
		}

		return c;
	}

	bool IsWhitespace(string c)
	{
		if (c == " ")
			return true;
		if (c == "\t")
			return true;
		if (c == "\n")
			return true;
		if (c == "\r")
			return true;

		//if ( c == "" )
		//	Error( "Unexpected end of string" );

		return false;
	}

	bool IsLetterOrDigit(string c)
	{
		return IsLetterOrDigit(c, false);
	}

	bool IsLetterOrDigit(string c, bool isQuoted)
	{
		int i = c.ToAscii();
		if (i >= 255 || i < 0) //! To my dear @DaOne, please don't use UTF-8 characters :)
			return true;

		if (i < 32)
			return false;

		if (isQuoted && i >= 32 && i <= 126)
			return true;

		if (i >= 48 && i <= 57)
			return true;

		if (i == 95)
			return true;

		if (i > 90)
			i -= 32;

		if (i >= 65 && i <= 90)
			return true;

		return false;
	}

	string SkipWhitespace()
	{
		string c = GetCharacter();
		while (IsWhitespace(c) && !EOF())
			c = GetCharacter();

		return c;
	}

	string GetWord()
	{
		string word = "";

		string c = SkipWhitespace();

		while (IsLetterOrDigit(c) && !EOF())
		{
			word = word + c;
			c = GetCharacter();
		}

		BackChar();

		return word;
	}

	string GetQuotedWord(out bool isQuoted)
	{
		string word = "";

		string c = SkipWhitespace();

		if (c == "\"")
		{
			c = "";
			isQuoted = true;
		}

		while ((IsLetterOrDigit(c, isQuoted) || c == "") && !EOF())
		{
			word = word + c;
			c = GetCharacter();
			if (isQuoted && c == "\"")
			{
				break;
			}
		}

		if (!isQuoted)
			BackChar();

		return word;
	}
};
