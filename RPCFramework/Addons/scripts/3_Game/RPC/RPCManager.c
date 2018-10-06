class RPCObject
{
    protected Class m_Object;
	protected string m_strCallbackFunction;

    protected bool m_SingleplayerUseServer;

    void RPCObject( Class object, string callback, bool singleplayerUseServer ) 
	{
		m_Object = object;
		
		m_strCallbackFunction = callback;
        
        m_SingleplayerUseServer = singleplayerUseServer;
	}
    
    Class GetObject() 
	{
		return m_Object;
	}
	
	string GetCallBackFunction() 
	{
		return m_strCallbackFunction;
	}

	bool SinglePlayerUsesServer() 
	{
		return m_SingleplayerUseServer;
	}
}

class RPCManager
{
    private ref map< int, ref RPCObject > m_RPCActions;

    private int m_LastRPCID;

    void RPCManager()
    {
        m_RPCActions = new ref map< int, ref RPCObject >;
        m_LastRPCID = 1000;
    }

    void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
    {
        Debug.Log( "Recieving" + rpc_type.ToString() );
        Print( "Recieving " + rpc_type.ToString() );

        ref RPCObject rpcObject;

        if ( m_RPCActions.Find( rpc_type, rpcObject ) )
        {
            Print( "Found the RPC?" );
            Param6<Class,Class,Class,Class,Class,Class> params;

            Print( ctx.ToString() );
            Print( ctx );

            if ( ctx.Read( params ) )
            {
                Print( "Converted the RPC?" );
                RunRPC( rpcObject, params, sender, target );
            }
        }
    }

    protected void RunRPC( ref RPCObject rpcObject, ref Param params, ref PlayerIdentity sender, ref Object target )
    {
        if ( GetGame().IsServer() && GetGame().IsMultiplayer() || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && rpcObject.SinglePlayerUsesServer() ) ) 
        {
            GetGame().GameScript.CallFunctionParams(rpcObject.GetObject(), rpcObject.GetCallBackFunction() + "_OnServer", NULL, new Param3<Param, PlayerIdentity, Object>( params, sender, target ) );
        } else if ( GetGame().IsClient() || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && !rpcObject.SinglePlayerUsesServer() ) ) 
        {
            GetGame().GameScript.CallFunctionParams(rpcObject.GetObject(), rpcObject.GetCallBackFunction() + "_OnClient", NULL, new Param3<Param, PlayerIdentity, Object>( params, sender, target ) );
        }
    }

    void SendRPC( int rpc_type, Param params, PlayerIdentity sendToIdentity, Object sendToTarget, bool guaranteed = true )
    {
        ref RPCObject rpcObject;

        if ( m_RPCActions.Find( rpc_type, rpcObject ) )
        {
            if ( GetGame().IsMultiplayer() )
            {
                GetGame().RPCSingleParam( sendToTarget, rpc_type, params, guaranteed, sendToIdentity );

                Debug.Log( "Sending " + rpc_type.ToString() );
                Print( "Sending " + rpc_type.ToString() );
            } else {
                Debug.Log( "Calling " + rpc_type.ToString() );
                Print( "Calling " + rpc_type.ToString() );
                RunRPC( rpcObject, params, sendToIdentity, sendToTarget );
            }
        }
    }

    int AddRPC( Class object, string callBackFunc, bool singleplayerUseServer = true )
    {
        m_LastRPCID = m_LastRPCID + 1;
        m_RPCActions.Insert( m_LastRPCID, new ref RPCObject( object, callBackFunc, singleplayerUseServer ) );

        return m_LastRPCID;
    }
}

static ref RPCManager g_RPCManager;

static ref RPCManager GetRPCManager()
{
    if ( !g_RPCManager )
    {
        g_RPCManager = new ref RPCManager;

		DayZGame.Cast( GetGame() ).Event_OnRPC.Insert( g_RPCManager.OnRPC );
    }

    return g_RPCManager;
}