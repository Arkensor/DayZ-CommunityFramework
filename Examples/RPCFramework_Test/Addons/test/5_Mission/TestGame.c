class TestGame
{
    void TestGame()
    {
        GetRPCManager().AddRPC( "RPCTestMod", "TestRPCFunction", this, SingeplayerExecutionType.Client );
    }

    void TestRPCFunction( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< string > data;
		if ( !ctx.Read( data ) ) return;
		
		if( type == CallType.Server )
		{
			Print( "Server function called!" );
			
			data.param1 = "World, Hello!";
			
			if( GetGame().IsMultiplayer() ) //We don't need to forward the message again in singleplayer ... this is just for mp testing
			{
				GetRPCManager().SendRPC( "RPCTestMod", "TestRPCFunction", data, true, sender, target );
			}
		}
		else
		{
			Print( "Client function called!" );
			PlayerBase player = GetGame().GetPlayer();
			player.MessageStatus( data.param1 );
		}
    }

    void OnKeyPress( int key )
    {
        switch ( key )
        {
            case KeyCode.KC_K:
            {
                GetRPCManager().SendRPC( "RPCTestMod", "TestRPCFunction", new Param1< string >( "Hello, World!" ) );
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

        Print( "Loaded Server Mission" );
    }
};

modded class MissionGameplay
{
    ref TestGame m_TestGame;

    void MissionGameplay()
    {
        m_TestGame = new ref TestGame();

        Print( "Loaded Client Mission" );
    }

    override void OnKeyPress( int key )
    {
        super.OnKeyPress( key );

        m_TestGame.OnKeyPress( key );
    }
};