class RPCObject
{
    protected Class m_Object;
	protected string m_strCallbackFunction;
	protected string m_strShortcut;
	protected string m_strDescription;

    void RPCObject( Class object, string callback, string shortcut = "", string description = "" ) 
	{
		m_Object = object;
		
		m_strCallbackFunction = callback;
		m_strShortcut = shortcut;
		m_strDescription = description;
	}
    
    Class GetObject() 
	{
		return m_Object;
	}
	
	string GetShortcut() 
	{
		return m_strShortcut;
	}
	
	string GetDescription() 
	{
		return m_strDescription;
	}
	
	string GetCallBackFunction() 
	{
		return m_strCallbackFunction;
	}
}

class RPCManager
{
    private ref map< int, ref RPCObject > m_RPCActions;

    private int m_LastRPCID;
    
    private ref array<ref Param> m_ParamCache;

    void RPCManager()
    {
        m_RPCActions = new ref map< int, ref RPCObject >;

		m_ParamCache = new array<ref Param>;
		m_ParamCache.Insert( NULL );
    }

    void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
    {
        ref RPCObject rpcObject;

        if ( m_RPCActions.Find( rpc_type, rpcObject ) )
        {
            Param param;

            if ( ctx.Read( param ) )
            {
                if ( GetGame().IsClient() )
                {
                    Print( "Because GetPlayer doesn't work!!!" );
                }
                GetGame().GameScript.CallFunctionParams(rpcObject.GetObject(), rpcObject.GetCallBackFunction(), NULL, new Param3<Param, PlayerIdentity, Object>(param, sender, target)  );
            }
        }
    }

    void SendRPC( int rpc_type, Param param, PlayerIdentity sendToIdentity, Object sendToTarget, bool guaranteed = true )
    {
        ref RPCObject rpcObject;

        if ( m_RPCActions.Find( rpc_type, rpcObject ) )
        {
            if ( GetGame().IsMultiplayer() )
            {
		        m_ParamCache.Set(0, param);

                GetDayZGame().RPC( sendToTarget, rpc_type, m_ParamCache, guaranteed, sendToIdentity );
            } else {
                GetGame().GameScript.CallFunctionParams(rpcObject.GetObject(), rpcObject.GetCallBackFunction(), NULL, new Param3<Param, PlayerIdentity, Object>(param, sendToIdentity, sendToTarget) );
            }
        }
    }

    int AddRPC( Class object, string callBackFunc )
    {
        m_LastRPCID = m_LastRPCID + 1;
        m_RPCActions.Insert( m_LastRPCID, new ref RPCObject( object, callBackFunc ) );

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