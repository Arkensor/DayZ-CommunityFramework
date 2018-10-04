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

        switch ( key )
        {
            case KeyCode.KC_K:
            {
                PlayerBase player = GetGame().GetPlayer();

                ref RPCManager rpcmanager = GetRPCManager();
                if ( !rpcmanager )
                {
                    player.MessageStatus( "RPCManager does not exist!" );
                    break;
                }

                player.MessageStatus( "Sending Test RPC" );
                RPCTestAction testAction = GetRPCManager().GetAction( RPCMANAGER_UNKNOWN_TYPE + 1 );
                if ( testAction )
                {
                    testAction.Send( 0 );
                    player.MessageStatus( "Sent Test RPC" );
                } else {
                    player.MessageStatus( "Failed to send Test RPC" );
                }
                break;
            }
        }
    }
}