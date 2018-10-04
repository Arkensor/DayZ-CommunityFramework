modded class MissionGameplay
{
    void MissionGameplay()
    {
        Print( "Loaded TestGameplay");
        GetRPCManager().AddAction( new RPCTestAction );
    }

    override void OnKeyPress( int key )
    {
        super.OnKeyPress( key );

        if ( key == KeyCode.KC_K )
        {
            GetGame().GetPlayer().MessageStatus( "Sending Test RPC" );
            RPCTestAction testAction = GetRPCManager().GetAction( RPCMANAGER_UNKNOWN_TYPE + 1 );
            if ( testAction )
            {
                testAction.Send( 0 );
                GetGame().GetPlayer().MessageStatus( "Sent Test RPC" );
            } else {
                GetGame().GetPlayer().MessageStatus( "Failed to send Test RPC" );
            }
        }
    }
}