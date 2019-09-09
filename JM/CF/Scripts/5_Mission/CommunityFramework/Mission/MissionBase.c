modded class MissionBase
{
    void MissionBase()
    {
        if ( !ModuleManagerExists() )
        {
            Print( "Creating ModuleManager" );

            CreateModuleManager( new JMModuleConstructor );
        } else
        {
            Print( "Ignoring creation of ModuleManager" );
        }
    }
};