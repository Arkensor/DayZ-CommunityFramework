class CF_Lexer
{
	CF_Location m_Location;
	string m_Source;

	ref array<CF_Token> m_Tokens;
	int m_CurrentToken;

	static CF_Lexer Load(string path, string oldSource = "")
	{
		FileHandle fileHandle = OpenFile(path, FileMode.READ);

		string source;

		string lineContent;
		while (FGets(fileHandle, lineContent) >= 0)
		{
			source += lineContent + "\n";
		}

		CloseFile(fileHandle);

		if (source == oldSource)
		{
			return null;
		}

		CF_Lexer lexer = new CF_Lexer(source);
		return lexer;
	}

	void CF_Lexer(string source)
	{
		m_Source = source;

		m_Location = new CF_Location();
		m_Location.m_Lexer = this;
		m_Location.m_Position = -1;

		m_Tokens = new array<CF_Token>();
		m_CurrentToken = 0;

		while (!EndOfSource())
		{
			SkipWhitespace();

			CF_Location location = m_Location.Copy();

			if (ParseTokenIndices())
			{
				delete location;
				continue;
			}

			delete m_Location;
			m_Location = location;

			bool isQuoted = false;
			string value = ParseString(isQuoted);

			if (isQuoted)
			{
				AddToken(CF_Token.Create(value, CF_TokenType.QUOTE, m_Location, CF_TokenFlag.NONE));
				continue;
			}

			if (ParseNumber(value))
			{
				AddToken(CF_Token.Create(value, CF_TokenType.NUMBER, m_Location, CF_TokenFlag.NONE));
				continue;
			}

			AddToken(CF_Token.Create(value, CF_TokenType.TEXT, m_Location, CF_TokenFlag.NONE));
		}
	}

	void ~CF_Lexer()
	{
		Cleanup();
	}

	void Cleanup()
	{
		m_Tokens.Clear();
	}

	int Count()
	{
		return m_Tokens.Count();
	}

	CF_Token GetToken()
	{
		return m_Tokens[m_CurrentToken];
	}

	CF_Token GetTokenAndProgress()
	{
		return m_Tokens[m_CurrentToken++];
	}

	bool NextToken()
	{
		m_CurrentToken++;

		return m_CurrentToken >= 0 && m_CurrentToken < m_Tokens.Count();
	}

	bool PreviousToken()
	{
		m_CurrentToken--;

		return m_CurrentToken >= 0 && m_CurrentToken < m_Tokens.Count();
	}

	bool HasNext()
	{
		return (m_CurrentToken + 1) < m_Tokens.Count();
	}

	CF_TokenType GetTokenType()
	{
		return m_Tokens[m_CurrentToken].m_Type;
	}

	string GetTokenValue()
	{
		return m_Tokens[m_CurrentToken].m_Value;
	}

	string GetRelevantSource(int minOffset, int maxOffset)
	{
		int tokenPosition = m_CurrentToken;
		if (tokenPosition >= m_Tokens.Count())
		{
			tokenPosition = m_Tokens.Count() - 1;
		}

		auto token = m_Tokens[tokenPosition];

		int position = token.m_Location.m_Position - minOffset;
		int length = minOffset + maxOffset;
		if (position < 0) position = 0;
		if (position + length >= m_Source.Length()) length = m_Source.Length() - position;

		return m_Source.Substring(position, length);
	}

	void Warn(string message)
	{
		if (CF_Log.Level > CF_LogLevel.WARNING) return;

		array<string> lines();
		int i;
		auto location = m_Tokens[m_CurrentToken].m_Location;

		PrintFormat("[WARNING] [%1:%2] %3", location.m_Row, location.m_Column, message);

		string source = GetRelevantSource(20, 20);
		lines.Clear();
		source.Split("\n", lines);
		Print("\tContent:");
		for (i = 0; i < lines.Count(); i++)
			Print("\t\t" + lines[i]);

		string stack;
		DumpStackString(stack);

		lines.Clear();
		stack.Split("\n", lines);
		Print("\nStack Trace:");
		for (i = 0; i < lines.Count(); i++)
			Print("\t\t" + lines[i]);
	}

	void Error(string message)
	{
		if (CF_Log.Level > CF_LogLevel.ERROR) return;

		array<string> lines();
		int i;
		auto location = m_Tokens[m_CurrentToken].m_Location;

		PrintFormat("[ERROR] [%1:%2] %3", location.m_Row, location.m_Column, message);

		string source = GetRelevantSource(20, 20);
		lines.Clear();
		source.Split("\n", lines);
		Print("\tContent:");
		for (i = 0; i < lines.Count(); i++)
			Print("\t\t" + lines[i]);

		string stack;
		DumpStackString(stack);

		lines.Clear();
		stack.Split("\n", lines);
		Print("\tStack Trace:");
		for (i = 0; i < lines.Count(); i++)
			Print("\t\t" + lines[i]);
	}

	bool ParseTokenIndices()
	{
		string data;
		data += ReadCharacter();

		int size = CF_Tokens.Count();
		int previousPosition = m_Location.m_Position;
		for (int index = 1; index < size; index++)
		{
			data += NextValidCharacter();
			if (m_Location.m_Position - previousPosition > 1)
			{
				m_Location.m_Position = previousPosition + 1;
				size = index + 1;
				break;
			}

			previousPosition = m_Location.m_Position;
		}

		string nextCharacter = ReadCharacter();
		for (index = size; index > 0; index--)
		{
			size = index - 1;

			if (ParseTokens(CF_Tokens[size], data, nextCharacter))
			{
				BackCharacter();
				return true;
			}

			nextCharacter = BackCharacter();
			data = data.Substring(0, size);
		}

		return false;
	}

	bool ParseTokens(array<CF_Token> tokens, string data, string nextCharacter)
	{
		foreach (auto token : tokens)
		{
			if (token.Equals(data))
			{
				if (token.m_Flag == CF_TokenFlag.FAIL_IF_LACK_OF_WHITESPACE && !CF_Encoding.IsWhitespace(nextCharacter))
				{
					continue;
				}

				AddToken(CF_Token.Create(token, m_Location));
				return true;
			}
		}

		return false;
	}

	string ParseString(out bool isQuoted)
	{
		string word;

		string c = NextValidCharacter();

		isQuoted = false;
		if (c == "\"")
		{
			isQuoted = true;
			c = ReadCharacter();
		}
		else if (c == "-" || c == "+")
		{
			// ParseTokenIndices will have already verified a valid character is next
			word += c;
			c = ReadCharacter();
		}

		bool isNumber = ParseNumber(c);

		int previousPosition = m_Location.m_Position;
		while (!EndOfSource())
		{
			if (isQuoted)
			{
				if (c == "\"") break;

				word += c;
				c = ReadCharacter();
			}
			else
			{
				if (!((isNumber && c == ".") || CF_Encoding.IsAlphanumeric(c) || (!isNumber && c == "_"))) break;

				word += c;

				if (m_Location.m_Position - previousPosition > 1) break;
				previousPosition = m_Location.m_Position;

				c = NextValidCharacter();
			}

			if (!(isNumber && c == "."))
				isNumber &= ParseNumber(c);
		}

		if (!isQuoted)
		{
			BackCharacter();
		}

		return word;
	}

	bool ParseNumber(string value)
	{
		if (value.Length() == 0)
		{
			return false;
		}

		return ParseNumber(value[0].Hash());
	}

	bool ParseNumber(int value)
	{
		if (!(value == 45 || value == 43) && (value < 48 || value > 57))
		{
			return false;
		}

		return true;
	}

	void AddToken(CF_Token token)
	{
		m_Tokens.Insert(token);
	}

	bool EndOfSource()
	{
		return m_Location.m_Position + 1 >= m_Source.Length();
	}

	void SkipLine()
	{
		string c = ReadCharacter();
		while (c != "\n" && !EndOfSource())
		{
			c = ReadCharacter();
		}

		BackCharacter();
	}

	void SkipComment()
	{
		string c = ReadCharacter();
		while (!EndOfSource())
		{
			while (c != "*" && !EndOfSource())
				c = ReadCharacter();

			c = ReadCharacter();
			if (c == "/")
				return;
		}
	}

	string NextValidCharacter()
	{
		string c = ReadCharacter();

		while (!EndOfSource())
		{
			if (c == "/")
			{
				c = ReadCharacter();
				if (c == "/")
				{
					SkipLine();
				}
				else if (c == "*")
				{
					SkipComment();
				}
				else
				{
					BackCharacter();
					return "/";
				}
			}
			else
			{
				break;
			}

			c = ReadCharacter();
		}

		return c;
	}

	string ReadCharacter()
	{
		m_Location.m_Position += 1;
		if (m_Location.m_Position >= m_Source.Length())
			return "\0";

		string c = m_Source[m_Location.m_Position];
		if (c == "\n")
		{
			++m_Location.m_Row;
			m_Location.m_Column = 0;
		}
		else
		{
			m_Location.m_Column++;
		}

		return c;
	}

	string BackCharacter()
	{
		m_Location.m_Position -= 1;
		if (m_Location.m_Position < 0 || m_Location.m_Position >= m_Source.Length())
			return "\0";

		string c = m_Source[m_Location.m_Position];
		if (c == "\n")
		{
			--m_Location.m_Row;
			m_Location.m_Column = 0;

			int pos = m_Location.m_Position;
			while (pos > 0 && m_Source[pos] != "\n")
			{
				++m_Location.m_Column;
				--pos;
			}

			if (pos == 0) ++m_Location.m_Column;
		}
		else
		{
			m_Location.m_Column--;
		}

		return c;
	}

	void SkipWhitespace()
	{
		string character = NextValidCharacter();
		while (CF_Encoding.IsWhitespace(character))
		{
			character = NextValidCharacter();
		}

		BackCharacter();
	}
};
