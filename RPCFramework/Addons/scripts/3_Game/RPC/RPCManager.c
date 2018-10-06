class RPCWrapper
{
    protected Class m_Instance;
	protected string m_CallbackFunction;
    protected bool m_SingleplayerUseServer;

    void RPCWrapper( Class instance, string callBackFunc, bool singleplayerUseServer ) 
	{
		m_Instance = instance;
		
		m_CallbackFunction = callBackFunc;
		
        m_SingleplayerUseServer = singleplayerUseServer;
	}
    
    Class GetInstance() 
	{
		return m_Instance;
	}
	
	string GetCallBackFunction() 
	{
		return m_CallbackFunction;
	}
	
	bool GetAllowServerFunctionInSingeplayer() 
	{
		return m_SingleplayerUseServer;
	}
};

class RPCManager
{
	protected int m_LastRPCId;
    protected ref map< int, ref RPCWrapper > m_RPCActions;
    protected ref map< string, int > m_AliasMapping;

    void RPCManager()
    {
        m_RPCActions = new ref map< int, ref RPCWrapper >;
        m_AliasMapping = new ref map< string, int >;
        m_LastRPCId = 1000;
		
		GetDayZGame().Event_OnRPC.Insert( OnRPC );
    }

    void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
    {
        ref RPCWrapper wrapper;

        if ( m_RPCActions.Find( rpc_type, wrapper ) )
        {
			RunRPC( wrapper, ctx, sender, target );
        }
    }

    protected void RunRPC( ref RPCWrapper wrapper, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		auto fncName = wrapper.GetCallBackFunction();
		
        if( ( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && wrapper.GetAllowServerFunctionInSingeplayer() ) ) 
        {
			fncName += "_OnServer";
        }
		else
		{
			fncName += "_OnClient";
		}
		
		auto functionCallData = new Param3< ref ParamsReadContext, ref PlayerIdentity, ref Object >( ctx, sender, target );
		
		GetGame().GameScript.CallFunctionParams( wrapper.GetInstance(), fncName, NULL, functionCallData );
    }

    void SendRPC( string funcName, ref Param params, bool guaranteed = true, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL)
    {
		if( m_AliasMapping.Contains( funcName ) )
		{
			// if ( GetGame().IsMultiplayer() ) //Todo remove commented section if Jacob agrees on the way to use it like this.
			// {
				GetGame().RPCSingleParam( sendToTarget, m_AliasMapping[ funcName ], params, guaranteed, sendToIdentity );
			// } 
			// else 
			// {
				// ref RPCWrapper wrapper;

				// if ( m_RPCActions.Find( m_AliasMapping[ funcName ], wrapper ) )
				// {
					// auto ctx = new ScriptRPC;
					// ctx.Write( params );
					
					// RunRPC( wrapper, ctx, sendToIdentity, sendToTarget );
				// }
			// }
		}
    }

    bool AddRPC( Class instance, string callBackFunc, bool singleplayerUseServer = true )
    {
		if( !m_AliasMapping.Contains( callBackFunc ) )
		{
			m_LastRPCId++;
			
			auto wrapper = new ref RPCWrapper( instance, callBackFunc, singleplayerUseServer );
			
			m_RPCActions.Set( m_LastRPCId, wrapper );
			m_AliasMapping.Set( callBackFunc, m_LastRPCId );
			
			return true;
		}
		
		return false;
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