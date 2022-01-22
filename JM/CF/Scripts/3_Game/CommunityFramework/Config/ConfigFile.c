class ConfigFile : ConfigClass
{
	private ref ConfigReader _reader;

	private void ConfigFile()
	{
	}

	override string GetType()
	{
		return "FILE";
	}

	static ConfigFile Parse( string fileName )
	{
		ConfigFile file = new ConfigFile();

		file.Parse( ConfigReader.Open( fileName ), file );

		return file;
	}
};