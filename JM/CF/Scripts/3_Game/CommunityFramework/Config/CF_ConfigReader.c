typedef CF_ConfigReader ConfigReader;

class CF_ConfigReader : CF_Lexer
{
	static CF_Lexer Open(string path, string oldSource = "")
	{
		Load(path, oldSource);
	}
};
