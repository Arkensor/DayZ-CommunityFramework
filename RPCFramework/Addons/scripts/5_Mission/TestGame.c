class TestGame
{
    void TestGame()
    {
        GetRPCManager().AddRPC( this, "TestRPCCommand", false );
    }

    void TestRPCCommand_OnServer( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< int > data;
		ctx.Read( data );

        auto rpc = GetRPCManager();

        if ( !rpc || !data )
        {
            return;
        }

        rpc.SendRPC( "TestRPCCommand", data, true, sender, target );
    }

    void TestRPCCommand_OnClient( ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< int > data;
		ctx.Read( data );
		
        PlayerBase player = GetGame().GetPlayer();
        player.MessageStatus( "Recieved the data " + data.param1 );
    }

    void OnKeyPress( int key )
    {
        switch ( key )
        {
            case KeyCode.KC_K:
            {
                auto rpc = GetRPCManager();
				
                if ( !rpc )
                {
					PlayerBase player = GetGame().GetPlayer();
                    player.MessageStatus( "RPCManager does not exist!" );
                    break;
                }

				Param1< int > sendData = new Param1< int >( 10 );
				rpc.SendRPC( "TestRPCCommand", sendData );
				
                break;
            }
        }
    }
};