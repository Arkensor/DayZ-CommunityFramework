class E_TEST_RPCS
{
    static int RPC_TEST = -1;
}

class TestGame
{
    void TestGame()
    {
        E_TEST_RPCS.RPC_TEST = GetRPCManager().AddRPC( this, "TestRPCCommand", false );
    }

    void TestRPCCommand_OnServer( ref Param1< int > param, ref PlayerIdentity sender, ref Object target )
    {
        ref RPCManager rpcmanager = GetRPCManager();

        if ( !rpcmanager && !param )
        {
            return;
        }

        rpcmanager.SendRPC( E_TEST_RPCS.RPC_TEST, param, NULL, NULL );
    }

    void TestRPCCommand_OnClient( ref Param1< int > param, ref PlayerIdentity sender, ref Object target )
    {
        PlayerBase player = GetGame().GetPlayer();
        player.MessageStatus( "Recieved the param " + param.param1 );
    }

    void OnKeyPress( int key )
    {
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

                rpcmanager.SendRPC( E_TEST_RPCS.RPC_TEST, new ref Param1< int >( 10 ), NULL, NULL );
                break;
            }
        }
    }
}