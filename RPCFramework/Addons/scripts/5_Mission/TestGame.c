//#define RPCFRAMEWORK_TESTING

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

        data.param1 = "World, Hello!";

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

modded class MissionServer
{
    ref TestGame m_TestGame;

    void MissionServer()
    {
        m_TestGame = new ref TestGame();

        Print( "Loaded Server Mission");
    }
};

modded class MissionGameplay
{
    ref TestGame m_TestGame;

    void MissionGameplay()
    {
        m_TestGame = new ref TestGame();

        Print( "Loaded Client Mission");
    }

    override void OnKeyPress( int key )
    {
        super.OnKeyPress( key );

        m_TestGame.OnKeyPress( key );
    }
};
#endif