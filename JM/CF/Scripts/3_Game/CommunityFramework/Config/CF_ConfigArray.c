typedef CF_ConfigArray ConfigClass;

class CF_ConfigArray : CF_ConfigEntry
{
	override string GetType()
	{
		return "ARRAY";
	}

	override bool IsArray()
	{
		return true;
	}

	override CF_ConfigArray GetArray()
	{
		return this;
	}

	override bool Parse(CF_Lexer lexer, CF_ConfigClass root)
	{
		CF_Token token;

		token = lexer.GetToken();
		lexer.NextToken();

		if (!token.Equals(CF_Token.LeftCurlyBracket))
		{
			lexer.Error("Expected '{', got '" + token.m_Value + "'");
			return false;
		}

		while (lexer.HasNext())
		{
			token = lexer.GetToken();
			lexer.NextToken();

			//Print(token.m_Value);

			CF_ConfigArrayParam entry = NULL;

			if (token.Equals(CF_Token.LeftCurlyBracket))
			{
				entry = new CF_ConfigArrayParamArray();
				entry._parent = this;
				if ( !entry.Parse(lexer, root))
					return false;
			}
			else
			{
				string value = token.m_Value;
				switch (token.m_Type)
				{
					case CF_TokenType.QUOTE:
						entry = new CF_ConfigArrayParamText();
						entry.SetText(value);
						entry._parent = this;
						break;
					case CF_TokenType.NUMBER:
						if (value.Contains("."))
						{
							entry = new CF_ConfigArrayParamFloat();
							entry.SetFloat(value.ToFloat());
							entry._parent = this;
						}
						else
						{
							entry = new CF_ConfigArrayParamInt();
							entry.SetInt(value.ToInt());
							entry._parent = this;
						}
						break;
				}
			}

			if (entry)
				_entries.Insert( entry );

			token = lexer.GetToken();
			lexer.NextToken();

			if (token.Equals(CF_Token.RightCurlyBracket))
			{
				return true;
			}

			if (!token.Equals(CF_Token.Comma) && !token.Equals(CF_Token.SemiColon))
			{
				lexer.Error("Expected ',' or ';', got '" + token.m_Value + "'");
				return false;
			}
		}

		return false;
	}
};
