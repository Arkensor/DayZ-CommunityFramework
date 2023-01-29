typedef CF_ConfigFile ConfigFile;

class CF_ConfigFile : CF_ConfigClass
{
	override string GetType()
	{
		return "FILE";
	}

	static CF_ConfigFile Parse(string fileName)
	{
		CF_Lexer lexer = CF_Lexer.Load(fileName);

		if (lexer == null)
		{
			return null;
		}

		CF_ConfigFile file = new CF_ConfigFile();
		if (!Parse(lexer, file))
		{
			return null;
		}

		return file;
	}
};
