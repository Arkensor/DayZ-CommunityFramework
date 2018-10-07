class RPCMetaWrapper
{
    protected Class m_Instance;
    protected bool m_SingleplayerUseServer;

    void RPCMetaWrapper( Class instance, bool singleplayerUseServer ) 
	{
		m_Instance = instance;
		
        m_SingleplayerUseServer = singleplayerUseServer;
	}
    
    Class GetInstance() 
	{
		return m_Instance;
	}
	
	// Determines if the server or client function is what is called in singleplayer mode
	bool ServerFunctionCalledInSingleplayer() 
	{
		return m_SingleplayerUseServer;
	}
};

class RPCManager
{
	protected const int FRAMEWORK_RPC_ID = 10042;
    protected ref map< string, ref map< string, ref RPCMetaWrapper > > m_RPCActions;

    void RPCManager()
    {
        m_RPCActions = new ref map< string, ref map< string, ref RPCMetaWrapper > >;
		GetDayZGame().Event_OnRPC.Insert( OnRPC );
    }

    void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
    {
		if( rpc_type != FRAMEWORK_RPC_ID )
		{
			return;
		}
		
		Param2< string, string > metaData
		ctx.Read( metaData );
		
		string modName = metaData.param1;
		string funcName = metaData.param2;
		
		if( m_RPCActions.Contains( modName ) )
		{
			if( m_RPCActions[ modName ].Contains( funcName ) )
			{
				ref RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];

				if( ( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && wrapper.ServerFunctionCalledInSingleplayer() ) ) 
				{
					funcName += "_OnServer";
				}
				else
				{
					funcName += "_OnClient";
				}
				
				auto functionCallData = new Param3< ref ParamsReadContext, ref PlayerIdentity, ref Object >( ctx, sender, target );
				
				GetGame().GameScript.CallFunctionParams( wrapper.GetInstance(), funcName, NULL, functionCallData );
			}
		}
    }

    void SendRPC( string modName, string funcName, ref Param params, bool guaranteed = true, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL)
    {
		auto sendData = new ref array< ref Param >;
		sendData.Insert( new ref Param2< string, string >( modName, funcName ) );
		sendData.Insert( params );
		GetGame().RPC( sendToTarget, FRAMEWORK_RPC_ID, sendData, guaranteed, sendToIdentity );
    }

    bool AddRPC( string modName, string funcName, Class instance, bool singleplayerUseServer = true )
    {
		if( !m_RPCActions.Contains( modName ) )
		{
			m_RPCActions.Set( modName, new ref map< string, ref RPCMetaWrapper > );
		}
		
		auto wrapper = new ref RPCMetaWrapper( instance, singleplayerUseServer );
		
		m_RPCActions[ modName ].Set( funcName, wrapper );

		return true;
    }
};

static ref RPCManager g_RPCManager;

static ref RPCManager GetRPCManager()
{
    if ( !g_RPCManager )
    {
        g_RPCManager = new ref RPCManager;
    }

    return g_RPCManager;
}