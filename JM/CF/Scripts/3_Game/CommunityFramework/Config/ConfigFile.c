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

	static ref ConfigFile Parse( string fileName )
	{
		ref ConfigFile file = new ConfigFile();

		file.Parse( ConfigReader.Open( fileName ), file );

		return file;
	}
};