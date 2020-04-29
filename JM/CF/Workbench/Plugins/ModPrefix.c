static string g_ModPrefix;

static string GetWorkDriveDirectory()
{
	if ( g_ModPrefix != "" ) 
		return g_ModPrefix;

	if ( IsCLIParam( "" ) )
	{ 
		GetCLIParam( "", g_ModPrefix );

		array<string> tokens = new array<string>;
		g_ModPrefix.Split("\\", tokens);

		g_ModPrefix = "";

		for ( int i = 0; i < tokens.Count() - 1; i++ )
		{
			g_ModPrefix = g_ModPrefix + tokens[i] + "\\";
		}
	} else
	{
		g_ModPrefix = "P:\\JM\CF\\";
	}

	return g_ModPrefix;
}