static const int RPCMANAGER_UNKNOWN_TYPE = 1000;

class RPCManager
{
    private ref map< int, ref RPCActionBase > m_RPCActions;

    private int m_LastInsertedRPCType = RPCMANAGER_UNKNOWN_TYPE;

    void RPCManager()
    {
        m_RPCActions = new ref map< int, ref RPCActionBase >;
    }

    void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
    {
        ref RPCActionBase base;

        if ( m_RPCActions.Find( rpc_type, base ) )
        {
            if ( GetGame().IsServer() )
            {
                base.OnServer( ctx, sender, target );
            } else if ( GetGame().IsClient() )
            {
                base.OnClient( ctx, sender, target );
            }
        }
    }

    ref RPCActionBase GetAction( int id )
    {
        return m_RPCActions.Get( id );
    }

    void AddAction( ref RPCActionBase action )
    {
        if ( action )
        {
            m_LastInsertedRPCType = action.GetRPCType();
            m_RPCActions.Insert( action.GetRPCType(), action );
        }
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