typedef CF_ConfigClassDeclaration ConfigClassDeclaration;

class CF_ConfigClassDeclaration : CF_ConfigClass
{
	override bool IsClassDecl()
	{
		return true;
	}
};

typedef CF_ConfigDelete ConfigDelete;

class CF_ConfigDelete : CF_ConfigEntry
{
	override bool IsDelete()
	{
		return true;
	}
};

typedef CF_ConfigClass ConfigClass;

class CF_ConfigClass : CF_ConfigEntry
{
	private CF_ConfigClass _base;

	override string GetType()
	{
		return "CLASS";
	}

	static CF_ConfigClass Create(string name, CF_ConfigEntry parent = null)
	{
		CF_ConfigClass entry = new CF_ConfigClass();
		entry._name = name;
		if (parent && !parent.AddEntry(entry))
		{
			return null;
		}

		return entry;
	}

	override bool AddEntry(CF_ConfigEntry entry)
	{
		int idx = FindIndex(entry._name);
		if (idx < 0)
		{
			entry._parent = this;
			_entries.Insert(entry);
			return true;
		}

		return false;
	}

	override CF_ConfigClass GetClass()
	{
		return this;
	}

	CF_ConfigClass GetBase()
	{
		return _base;
	}

	private CF_ConfigClass SetBase(string name)
	{
		int baseIndex = _parent.FindIndex(name);
		int thisIndex = _parent.FindIndex(_name);
		if (baseIndex >= 0 && (baseIndex < thisIndex || thisIndex < 0))
		{
			return _parent._entries[baseIndex].GetClass();
		}

		CF_ConfigEntry possibleEntry = null;

		if (_parent.GetClass()._base != null)
		{
			possibleEntry = _parent.GetClass()._base.Find(name, true, true);
		}

		if (possibleEntry == null && _parent._parent != null)
		{
			possibleEntry = _parent._parent.GetClass().Find(name, true, true);
		}

		if (possibleEntry != null && possibleEntry.IsClass())
		{
			return possibleEntry.GetClass();
		}

		return null;
	}

	CF_ConfigEntry Find(string name, bool checkParent, bool checkBase)
	{
		name.ToLower();

		int idx = FindIndex(name, true);
		if (idx >= 0)
			return _entries[idx];

		CF_ConfigEntry entry = null;

		if (checkBase && _base != null)
		{
			entry = _base.Find(name, true, true);
			if (entry != null)
				return entry;
		}

		if (checkParent && _parent != null && _parent.GetClass() != null)
		{
			entry = _parent.GetClass().Find(name, true, checkBase);
			if (entry != null)
				return entry;
		}

		return null;
	}

	override bool Parse(CF_Lexer lexer, CF_ConfigClass root)
	{
		CF_Token token;

		while (lexer.HasNext())
		{
			token = lexer.GetToken();

			if (token.Equals(CF_Token.Hash))
			{
				lexer.Error("Not implemented.");
				return false;
			}
			else if (token.Equals(CF_Token.RightCurlyBracket))
			{
				lexer.NextToken();

				token = lexer.GetToken();
				lexer.NextToken();

				if (!token.Equals(CF_Token.SemiColon))
				{
					lexer.Error("Expected ';', got '" + token.m_Value + "'");
					return false;
				}

				return true;
			}

			CF_ConfigEntry entry = null;
			string name = "";

			lexer.NextToken();

			if (token.Equals("delete"))
			{
				token = lexer.GetToken();
				lexer.NextToken();
				name = token.m_Value;

				token = lexer.GetToken();
				lexer.NextToken();

				if (!token.Equals(CF_Token.SemiColon))
				{
					lexer.Error("Expected ';', got '" + token.m_Value + "'");
					return false;
				}

				entry = new CF_ConfigDelete();
				entry._name = name;
				entry._parent = this;
			}
			else if (token.Equals("class"))
			{
				token = lexer.GetToken();
				lexer.NextToken();
				name = token.m_Value;

				token = lexer.GetToken();
				lexer.NextToken();

				if (token.Equals(CF_Token.SemiColon))
				{
					entry = new CF_ConfigClassDeclaration();
					entry._name = name;
					entry._parent = this;
				}
				else
				{
					entry = new CF_ConfigClass();
					entry._name = name;
					entry._parent = this;

					if (token.Equals(CF_Token.Colon))
					{
						token = lexer.GetToken();
						lexer.NextToken();

						string baseName = token.m_Value;
						CF_ConfigEntry baseEntry = Find(baseName, true, true);
						if (baseEntry == null)
						{
							lexer.Error("Undefined base class '" + baseName + "'");
							return false;
						}

						if (!baseEntry.IsClass())
						{
							lexer.Error("'" + baseName + "' is not a class");
							return false;
						}

						entry.GetClass()._base = baseEntry.GetClass();

						token = lexer.GetToken();
						lexer.NextToken();
					}

					if (!token.Equals(CF_Token.LeftCurlyBracket))
					{
						lexer.Error("Expected '{', got '" + token.m_Value + "'");
						return false;
					}

					if (!entry.Parse(lexer, root))
						return false;
				}
			}
			else if (token.Equals("enum"))
			{
				lexer.Error("Enum is not supported");
				return false;
			}
			else
			{
				name = token.m_Value;

				token = lexer.GetToken();
				lexer.NextToken();
				if (token.Equals(CF_Token.LeftSquareBracket))
				{
					token = lexer.GetToken();
					lexer.NextToken();

					if (!token.Equals(CF_Token.RightSquareBracket))
					{
						lexer.Error("Expected ']', got '" + token.m_Value + "'");
						return false;
					}

					token = lexer.GetToken();
					lexer.NextToken();

					if (!token.Equals(CF_Token.Assignment))
					{
						lexer.Error("Expected '=', got '" + token.m_Value + "'");
						return false;
					}

					entry = new CF_ConfigArray();
					entry._name = name;
					entry._parent = this;
					if (!entry.Parse(lexer, root))
						return false;
				}
				else if (token.Equals(CF_Token.Assignment))
				{
					token = lexer.GetToken();
					lexer.NextToken();

					string value = token.m_Value;
					switch (token.m_Type)
					{
						case CF_TokenType.QUOTE:
							entry = new CF_ConfigValueText();
							entry._name = name;
							entry.SetText(value);
							entry._parent = this;
							break;
						case CF_TokenType.NUMBER:
							if (value.Contains("."))
							{
								entry = new CF_ConfigValueFloat();
								entry._name = name;
								entry.SetFloat(value.ToFloat());
								entry._parent = this;
							}
							else
							{
								entry = new CF_ConfigValueInt();
								entry._name = name;
								entry.SetInt(value.ToInt());
								entry._parent = this;
							}
							break;
					}
				}
				else
				{
					lexer.Error("Expected '=' or '[]', got '" + token.m_Value + "'");
					return false;
				}

				token = lexer.GetToken();
				lexer.NextToken();

				if (!token.Equals(CF_Token.SemiColon))
				{
					lexer.Error("Expected ';', got '" + token.m_Value + "'");
					return false;
				}
			}

			if (entry != null)
			{
				entry._name.ToLower();

				int idx = FindIndex(entry._name);
				if (idx < 0)
				{
					_entries.Insert(entry);
				} else
				{
					lexer.Error("'" + entry._name + "' already defined");
				}
			}
		}

		if (this == root)
		{
			return true;
		}

		lexer.Error("Unexpected EOF reached.");
		return false;
	}
};
