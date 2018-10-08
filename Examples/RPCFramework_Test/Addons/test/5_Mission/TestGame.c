class TestGame
{
    private static const string m_ModName = "RPCTestMod";

    void TestGame()
    {
        AddRPC( "TestRPCFunction", this, SingeplayerExecutionType.Both );
    }

    static void AddRPC( string funcName, Class instance, int singlePlayerExecType = SingeplayerExecutionType.Server )
    {
        GetRPCManager().AddRPC( m_ModName, funcName, params, singlePlayerExecType );
    }

    static void SendRPC( string funcName, ref Param params, bool guaranteed = true, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
    {
        GetRPCManager().SendRPC( m_ModName, funcName, params, guaranteed, sendToIdentity, sendToTarget );
    }

    void TestRPCFunction( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		Param1< string > data;
		if ( !ctx.Read( data ) ) return;
		
		if( type == CallType.Server )
		{
			data.param1 = "World, Hello!";
		}
		else
		{
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
                SendRPC( "TestRPCFunction", new Param1< string >( "Hello, World!" ) );
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