class JMModuleConstructorBase
{
    void Generate( out map< typename, ref JMModuleBase > moduleMap )
	{
		TTypenameArray moduleArrayNames = new TTypenameArray;
		RegisterModules( moduleArrayNames );

		// Sort( moduleArrayNames, moduleArrayNames.Count() );
		
		moduleMap = new map< typename, ref JMModuleBase >;
		
		for(int i = 0; i < moduleArrayNames.Count(); i++)
		{
			if ( moduleArrayNames[i].IsInherited( JMModuleBase ) )
			{
				moduleMap.Insert( moduleArrayNames[i], moduleArrayNames[i].Spawn() );
			}
		}
	}

    void RegisterModules( TTypenameArray modules )
	{
    }
}