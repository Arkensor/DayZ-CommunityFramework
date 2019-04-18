enum SingeplayerExecutionType
{
    Server = 0,
    Client,
    Both
}

enum SingleplayerExecutionType
{
    Server = 0,
    Client,
    Both
}

enum CallType
{
    Server = 0,
    Client
}

class RPCMetaWrapper
{
    protected Class m_Instance;
    protected int m_SPExecType;

    void RPCMetaWrapper( Class instance, int spExecType ) 
    {
        m_Instance = instance;
        
        m_SPExecType = spExecType;
    }
    
    Class GetInstance() 
    {
        return m_Instance;
    }
    
    // Determines if the server or client function is what is called in singleplayer mode
    int GetSPExecutionType() 
    {
        return m_SPExecType;
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
        if ( rpc_type != FRAMEWORK_RPC_ID )
        {
            return;
        }
        
        Param2< string, string > metaData;
        if ( !ctx.Read( metaData ) )
        {
            Error("Failed reading RPC!");
            return;
        }
        
        string modName = metaData.param1;
        string funcName = metaData.param2;
        
        if ( m_RPCActions.Contains( modName ) )
        {
            if ( m_RPCActions[ modName ].Contains( funcName ) )
            {
                ref RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];
                
                if ( wrapper.GetInstance() )
                {
                    auto functionCallData = new Param4< CallType, ref ParamsReadContext, ref PlayerIdentity, ref Object >( CallType.Server, ctx, sender, target );
                
                    if ( ( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecutionType() == SingleplayerExecutionType.Server || wrapper.GetSPExecutionType() == SingleplayerExecutionType.Both ) ) ) 
                    {
                        GetGame().GameScript.CallFunctionParams( wrapper.GetInstance(), funcName, NULL, functionCallData );
                    }

                    if ( ( GetGame().IsClient() && GetGame().IsMultiplayer() ) || ( GetGame().IsServer() && !GetGame().IsMultiplayer() && ( wrapper.GetSPExecutionType() == SingleplayerExecutionType.Client || wrapper.GetSPExecutionType() == SingleplayerExecutionType.Both ) ) ) 
                    {
                        //Update call type
                        functionCallData.param1 = CallType.Client;
                        GetGame().GameScript.CallFunctionParams( wrapper.GetInstance(), funcName, NULL, functionCallData );
                    }
                }
            }
        }
    }

    void SendRPC( string modName, string funcName, ref Param params, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
    {
        auto sendData = new ref array< ref Param >;
        sendData.Insert( new ref Param2< string, string >( modName, funcName ) );
        sendData.Insert( params );
        
        //In case we are in the singleplayer and the data is consumed twice for both client and server, we need to add it twice. Better than making a deep copy with more complicated rules on receiving
        if ( !GetGame().IsMultiplayer() )
        {
            if ( m_RPCActions.Contains( modName ) )
            {
                if ( m_RPCActions[ modName ].Contains( funcName ) )
                {
                    ref RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];
                    
                    if ( ( wrapper.GetSPExecutionType() == SingleplayerExecutionType.Both ) )
                    {
                        sendData.Insert( params );
                    }
                }
            }
        }

        GetGame().RPC( sendToTarget, FRAMEWORK_RPC_ID, sendData, guaranteed, sendToIdentity );
    }    

    /**
     * Warning: Does not support "SingleplayerExecutionType.Both"
     */
    void SendRPCs( string modName, string funcName, ref array< ref Param > params, bool guaranteed = false, ref PlayerIdentity sendToIdentity = NULL, ref Object sendToTarget = NULL )
    {
        params.InsertAt( new ref Param2< string, string >( modName, funcName ), 0 );

        GetGame().RPC( sendToTarget, FRAMEWORK_RPC_ID, params, guaranteed, sendToIdentity );

        if ( !GetGame().IsMultiplayer() )
        {
            if ( m_RPCActions.Contains( modName ) )
            {
                if ( m_RPCActions[ modName ].Contains( funcName ) )
                {
                    ref RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];
                    
                    if ( ( wrapper.GetSPExecutionType() == SingleplayerExecutionType.Both ) )
                    {
                        Error("[CF] " + modName + "::" + funcName + " does not support \"SingleplayerExecutionType.Both\" when using RPCManager::SendRPCs, use RPCManager::SendRPC instead!");
                    }
                }
            }
        }
    }

    bool AddRPC( string modName, string funcName, Class instance, int singlePlayerExecType = SingleplayerExecutionType.Server )
    {
        if( !m_RPCActions.Contains( modName ) )
        {
            m_RPCActions.Set( modName, new ref map< string, ref RPCMetaWrapper > );
        }
        
        auto wrapper = new ref RPCMetaWrapper( instance, singlePlayerExecType );
        
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