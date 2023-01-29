typedef CF_ConfigFile ConfigFile;

class CF_ConfigFile : CF_ConfigClass
{
	override string GetType()
	{
		return "FILE";
	}

	static ConfigFile Parse(string fileName)
	{
		CF_Lexer lexer = CF_Lexer.Load(fileName);

		if (lexer == null)
		{
			return null;
		}

		if (!Parse(lexer, this))
		{
			return null;
		}

		return this;
	}
};
