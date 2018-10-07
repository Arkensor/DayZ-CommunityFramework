#ifdef RPCFRAMEWORK_TESTING
class TestGame
{
    void TestGame()
    {
        GetRPCManager().AddRPC( this, "TestRPCCommand", false );
    }

    void TestRPCCommand_OnServer( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< string > data;
		if ( !ctx.Read( data ) ) return;

        GetRPCManager().SendRPC( "TestRPCCommand", data, true, sender, target );
    }

    void TestRPCCommand_OnClient( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< string > data;
		if ( !ctx.Read( data ) ) return;
		
        PlayerBase player = GetGame().GetPlayer();
        player.MessageStatus( "Recieved the data: " + data.param1 );
    }

    void OnKeyPress( int key )
    {
		PlayerBase player = GetGame().GetPlayer();

        switch ( key )
        {
            case KeyCode.KC_K:
            {
                auto rpc = GetRPCManager();
				
                if ( !rpc )
                {
                    player.MessageStatus( "RPCManager does not exist!" );
                    break;
                } else 
                {
                    player.MessageStatus( "Sending RPC!" );
                }

				rpc.SendRPC( "TestRPCCommand", new Param1< string >( "Hello, World!" ) );
				
                break;
            }
        }
    }
};
#endif