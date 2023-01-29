enum CF_TokenType
{
	UNKNOWN = 0,
	TEXT,
	QUOTE,
	NUMBER,
	DEFINTION
};

enum CF_TokenFlag
{
	NONE = 0,
	FAIL_IF_LACK_OF_WHITESPACE
};

static ref array<ref array<CF_Token>> CF_Tokens = new array<ref array<CF_Token>>();

class CF_Token : Class
{
	string m_Value;
	CF_Location m_Location;
	CF_TokenType m_Type;
	CF_TokenFlag m_Flag;

	bool Equals(string other)
	{
		return m_Value == other;
	}

	bool Equals(CF_Token other)
	{
		return m_Value == other.m_Value;
	}

	override string GetDebugName()
	{
		string str = super.GetDebugName();

		str += " Value=" + m_Value;

		if (m_Location)
		{
			str += " Location=[" + m_Location.GetDebugName() + "]";
		}
		else
		{
			str += " Location=null";
		}

		str += " Type=" + typename.EnumToString(CF_TokenType, m_Type);
		str += " Flag=" + typename.EnumToString(CF_TokenFlag, m_Flag);

		return str;
	}

	static CF_Token Create(CF_Token other, CF_Location location)
	{
		CF_Token token = new CF_Token();
		token.m_Value = other.m_Value;
		token.m_Location = location.Copy();
		token.m_Type = other.m_Type;
		token.m_Flag = other.m_Flag;

		return token;
	}

	static CF_Token Create(string value, CF_TokenType type, CF_Location location, CF_TokenFlag flag)
	{
		CF_Token token = new CF_Token();
		token.m_Value = value;
		token.m_Location = location.Copy();
		token.m_Type = type;
		token.m_Flag = flag;

		return token;
	}

	static CF_Token Create(string value, CF_TokenType type = 4 /*CF_TokenType.DEFINTION*/, CF_TokenFlag flag = 0 /*CF_TokenFlag.NONE*/)
	{
		CF_Token token = new CF_Token();
		token.m_Value = value;
		token.m_Location = null;
		token.m_Type = type;
		token.m_Flag = flag;

		int index = value.Length() - 1;
		int count = CF_Tokens.Count();

		if (CF_Tokens.Count() < value.Length())
		{
			for (int i = count; i < value.Length(); i++)
			{
				CF_Tokens.Insert(new array<CF_Token>());
			}
		}

		CF_Tokens[index].Insert(token);

		return token;
	}

	static CF_Token Addition = CF_Token.Create("+", CF_TokenType.DEFINTION, CF_TokenFlag.FAIL_IF_LACK_OF_WHITESPACE);
	static CF_Token Subtraction = CF_Token.Create("-", CF_TokenType.DEFINTION, CF_TokenFlag.FAIL_IF_LACK_OF_WHITESPACE);
	static CF_Token Multiplication = CF_Token.Create("*");
	static CF_Token Division = CF_Token.Create("/");
	static CF_Token Modulo = CF_Token.Create("%");
	static CF_Token BitwiseAND = CF_Token.Create("&");
	static CF_Token BitwiseOR = CF_Token.Create("|");
	static CF_Token BitwiseXOR = CF_Token.Create("^");
	static CF_Token BitwiseLeftShift = CF_Token.Create("<<");
	static CF_Token BitwiseRightShift = CF_Token.Create(">>");

	static CF_Token Assignment = CF_Token.Create("=");
	static CF_Token AdditionAssignment = CF_Token.Create("+=");
	static CF_Token SubtractionAssignment = CF_Token.Create("-=");
	static CF_Token MultiplicationAssignment = CF_Token.Create("*=");
	static CF_Token DivisionAssignment = CF_Token.Create("/=");
	static CF_Token ModuloAssignment = CF_Token.Create("%=");
	static CF_Token BitwiseANDAssignment = CF_Token.Create("&=");
	static CF_Token BitwiseORAssignment = CF_Token.Create("|=");
	static CF_Token BitwiseXORAssignment = CF_Token.Create("^=");
	static CF_Token BitwiseLeftShiftAssignment = CF_Token.Create("<<=");
	static CF_Token BitwiseRightShiftAssignment = CF_Token.Create(">>=");

	static CF_Token Increment = CF_Token.Create("++");
	static CF_Token Decrement = CF_Token.Create("--");

	static CF_Token Equal = CF_Token.Create("==");
	static CF_Token Greater = CF_Token.Create(">");
	static CF_Token GreaterEqual = CF_Token.Create(">=");
	static CF_Token Less = CF_Token.Create("<");
	static CF_Token LessEqual = CF_Token.Create("<=");
	static CF_Token NotEqual = CF_Token.Create("!=");

	static CF_Token Not = CF_Token.Create("!");

	static CF_Token Or = CF_Token.Create("||");
	static CF_Token And = CF_Token.Create("&&");

	static CF_Token LeftBracket = CF_Token.Create("(");
	static CF_Token RightBracket = CF_Token.Create(")");

	static CF_Token LeftCurlyBracket = CF_Token.Create("{");
	static CF_Token RightCurlyBracket = CF_Token.Create("}");

	static CF_Token LeftSquareBracket = CF_Token.Create("[");
	static CF_Token RightSquareBracket = CF_Token.Create("]");

	static CF_Token SemiColon = CF_Token.Create(";");
	static CF_Token Colon = CF_Token.Create(":");

	static CF_Token Comma = CF_Token.Create(",");
	static CF_Token Period = CF_Token.Create(".");

	static CF_Token At = CF_Token.Create("@");

	static CF_Token Hash = CF_Token.Create("#");
};
