class JMModuleConstructorBase
{
	void Generate( out map< typename, ref JMModuleBase > moduleMap )
	{
		array< typename > moduleArrayNames = new array< typename >;
		RegisterModules( moduleArrayNames );

		// Sort( moduleArrayNames, moduleArrayNames.Count() );

		string pNames[ 1000 ];
		int pIndices[ 1000 ];
		int i;
		int j;

		for ( i = 0; i < moduleArrayNames.Count(); i++ )
		{
			pNames[ i ] = moduleArrayNames[ i ].ToString();
		}

		Sort( pNames, moduleArrayNames.Count() );

		for ( i = 0; i < moduleArrayNames.Count(); i++ )
		{
			for ( j = 0; j < moduleArrayNames.Count(); j++ )
			{
				if ( pNames[ j ] == moduleArrayNames[ i ].ToString() )
				{
					pIndices[ i ] = j;
				}
			}
		}

		moduleMap = new map< typename, ref JMModuleBase >;
		
		for ( i = 0; i < moduleArrayNames.Count(); i++ )
		{
			int idx = pIndices[ i ];
			if ( moduleArrayNames[ idx ].IsInherited( JMModuleBase ) )
			{
				ref JMModuleBase module = JMModuleBase.Cast( moduleArrayNames[ idx ].Spawn() );

				if ( IsMissionHost() )
				{
					if ( module.IsServer() )
					{
						Print( "Inserted Module (HOST): " + module.GetModuleName() );
						moduleMap.Insert( moduleArrayNames[ idx ], module );
						continue;
					}
				}

				if ( IsMissionClient() )
				{
					if ( module.IsClient() )
					{
						Print( "Inserted Module (CLIENT): " + module.GetModuleName() );
						moduleMap.Insert( moduleArrayNames[ idx ], module );
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