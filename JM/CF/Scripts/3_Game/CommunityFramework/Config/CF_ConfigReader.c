typedef CF_ConfigReader ConfigReader;

class CF_ConfigReader : CF_Lexer
{
	// use CF_Lexer::Load
	static CF_Lexer Open(string path, string oldSource = "")
	{
		return Load(path, oldSource);
	}
};
