class RPCActionBase
{
	protected ref array<ref Param> m_ParamCache;

    void RPCActionBase()
    {
		m_ParamCache = new array<ref Param>;
		m_ParamCache.Insert( NULL );
    }

    int GetRPCType()
    {
        return 1000;
    }

    // Retrieves the data from the client to be called on the server.
    void OnServer( ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        ref Param params = ServerRead( ctx );
        if ( params )
        {
            PerformServer( params, sender, target );
        }
    }

    // Retrieves the data from the server to be called on the client.
    void OnClient( ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        ref Param params = ClientRead( ctx );
        if ( params )
        {
            PerformClient( params, sender, target );
        }
    }

    protected ref Param ServerRead( ParamsReadContext ctx )
    {
        return NULL;
    }

    protected ref Param ClientRead( ParamsReadContext ctx )
    {
        return NULL;
    }

    // Verifies the action
    protected bool VerifyAction( ref Param params, PlayerIdentity sender )
    {
        return true;
    }

    // Performs the action on the server (or in local multiplayer).
    protected void PerformServer( ref Param params, ref PlayerIdentity sender, ref Object target )
    {
    }

    // Performs the action on the client.
    protected void PerformClient( ref Param params, ref PlayerIdentity sender, ref Object target )
    {
    }

    // Sends the data to the server
    void SendServer( ref Param params )
    {
        if ( !GetGame().IsMultiplayer() )
        {
            PerformServer( params, NULL );
            return;
        }

        LogError( params.ToString() );

		m_ParamCache.Set(0, params);

        /*
        PlayerBase player = GetGame().GetPlayer();

        if ( player )
        {
            GetDayZGame().RPC( player, GetRPCType(), m_ParamCache, true, NULL );
        } else
        {
            GetDayZGame().RPC( NULL, GetRPCType(), m_ParamCache, true, NULL );
        }
        */

        GetDayZGame().RPC( NULL, GetRPCType(), m_ParamCache, true, NULL );
    }

    // Sends the data to the client(s)
    void SendClient( ref Param params, PlayerIdentity identity = NULL )
    {
        if ( GetGame().IsClient() ) 
        {
            LogError( "Trying to send data to a client, we are a client!" );
            return;
        }

        LogError( params.ToString() );

		m_ParamCache.Set(0, params);

        GetDayZGame().RPC( NULL, GetRPCType(), m_ParamCache, true, identity );
    }

    // Logs the error
    protected void LogError( string message )
    {
        Print( "RPC Error (" + GetRPCType() + "): " + message );
        Debug.Log( "RPC Error (" + GetRPCType() + "): " + message );
    }
}