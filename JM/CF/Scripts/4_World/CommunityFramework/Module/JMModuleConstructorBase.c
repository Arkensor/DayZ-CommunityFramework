class JMModuleConstructorBase
{
	void Generate( out map< typename, ref JMModuleBase > moduleMap, out array< JMModuleBase > moduleArr )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Generate").Add(moduleMap).Add(moduleArr);
		#endif

		array< typename > moduleArrayNames = new array< typename >;
		RegisterModules( moduleArrayNames );

		moduleMap = new map< typename, ref JMModuleBase >;
		moduleArr = new array< JMModuleBase >;
		
		for ( int idx = 0; idx < moduleArrayNames.Count(); idx++ )
		{
			typename moduleType = moduleArrayNames[ idx ];
			if ( moduleType.IsInherited( JMModuleBase ) )
			{
				ref JMModuleBase module = JMModuleBase.Cast( moduleType.Spawn() );

				if ( IsMissionHost() )
				{
					if ( module.IsServer() )
					{
						Print( "Inserted Module (HOST): " + module.GetModuleName() );
						moduleMap.Insert( moduleType, module );
						moduleArr.Insert( module );
						continue;
					}
				}

				if ( IsMissionClient() )
				{
					if ( module.IsClient() )
					{
						Print( "Inserted Module (CLIENT): " + module.GetModuleName() );
						moduleMap.Insert( moduleType, module );
						moduleArr.Insert( module );
						continue;
					}
				}

				Print( "Deleted Module: " + module.GetModuleName() );
				delete module;
				continue;
			}

			Print( "Failed Module: " + moduleType.ToString() );
		}
	}

	void RegisterModules( out array< typename > modules )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "RegisterModules").Add(modules);
		#endif

	}
}