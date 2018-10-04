static const int RPCMANAGER_UNKNOWN_TYPE = 1000;

class RPCManager
{
    private ref map< int, ref RPCActionBase > m_RPCActions;

    private int m_LastInsertedRPCType = RPCMANAGER_UNKNOWN_TYPE;

    void RPCManager()
    {
        m_RPCActions = new ref map< int, ref RPCActionBase >;

		DayZGame.Cast( GetGame() ).Event_OnRPC.Insert( this.OnRPC );
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

    RPCActionBase GetAction( int id )
    {
        return m_RPCActions.Get( id );
    }

    void AddAction( RPCActionBase action )
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
    return g_RPCManager;
}