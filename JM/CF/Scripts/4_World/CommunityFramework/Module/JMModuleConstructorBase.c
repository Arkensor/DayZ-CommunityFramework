class JMModuleConstructorBase
{
    void Generate( out map< typename, ref JMModuleBase > moduleMap )
	{
		ref array< typename > moduleArrayNames = new array< typename >;
		RegisterModules( moduleArrayNames );

		// Sort( moduleArrayNames, moduleArrayNames.Count() );
		
		moduleMap = new map< typename, ref JMModuleBase >;
		
		for ( int i = 0; i < moduleArrayNames.Count(); i++ )
		{
			if ( moduleArrayNames[i].IsInherited( JMModuleBase ) )
			{
				ref JMModuleBase module = moduleArrayNames[i].Spawn();

				if ( IsMissionHost() )
				{
					if ( module.IsServer() )
					{
						Print( "Inserted Module (HOST): " + module.GetModuleName() );
						moduleMap.Insert( moduleArrayNames[i], module );
						continue;
					}
				}

				if ( IsMissionClient() )
				{
					if ( module.IsClient() )
					{
						Print( "Inserted Module (CLIENT): " + module.GetModuleName() );
						moduleMap.Insert( moduleArrayNames[i], module );
						continue;
					}
				}

				Print( "Deleted Module: " + module.GetModuleName() );
				delete module;
				continue;
			}

			Print( "Failed Module: " + moduleArrayNames[i].ToString() );
		}
	}

    void RegisterModules( out array< typename > modules )
	{
    }
}