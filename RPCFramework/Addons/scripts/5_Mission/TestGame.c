class E_TEST_RPCS
{
    static int RPC_TEST = -1;
}

class TestGame
{
    void TestGame()
    {
        E_TEST_RPCS.RPC_TEST = GetRPCManager().AddRPC( this, "TestRPCCommand" );
    }

    void TestRPCCommand( ref Param getParams, ref PlayerIdentity sender, ref Object target = NULL )
    {
        if ( GetGame().IsServer() && GetGame().IsMultiplayer())
        {
            ref Param1< int > param = getParams;

            GetRPCManager().SendRPC( E_TEST_RPCS.RPC_TEST, param.param1, NULL, NULL );
        }

        if ( GetGame().IsClient() ) 
        {
            ref Param1< int > param = getParams;

            PlayerBase player = GetGame().GetPlayer();
            player.MessageStatus( "Recieved the param " + param.param1 );
        }
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

                GetRPCManager().SendRPC( E_TEST_RPCS.RPC_TEST, new ref Param1< int >( 10 ), sender, NULL );
                break;
            }
        }
    }
}