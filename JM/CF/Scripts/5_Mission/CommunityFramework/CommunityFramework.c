Mission CFMissionMain( string path )
{
    if ( !ModuleManagerExists() )
    {
        Print( "Creating ModuleManager" );

        CreateModuleManager( new JMModuleConstructor );
    } else
    {
        Print( "Ignoring creation of ModuleManager" );
    }

    return CreateMission( path );
}