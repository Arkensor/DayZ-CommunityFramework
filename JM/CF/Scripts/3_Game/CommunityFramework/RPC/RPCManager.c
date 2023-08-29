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
	static const int FRAMEWORK_RPC_ID = 10042;

	protected autoptr map< string, ref map< string, ref RPCMetaWrapper > > m_RPCActions = new map< string, ref map< string, ref RPCMetaWrapper > >;
	
	void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this).Add(sender).Add(target).Add(rpc_type).Add(ctx);
		#endif
		
		Param2< string, string > metaData;
		if ( !ctx.Read( metaData ) )
		{
			CF_Log.Warn( "Failed reading the RPC metadata!");
			return;
		}
		
		string modName = metaData.param1;
		string funcName = metaData.param2;

		string recievedFrom = "server";
		if ( GetGame().IsDedicatedServer() )
		{
			if ( sender == NULL )
			{
				CF_Log.Warn( "RPC sent from invalid sender!");
				return;
			}

			recievedFrom = sender.GetPlainId();
		}
		
		map< string, ref RPCMetaWrapper > functions;
		if ( m_RPCActions.Find( modName, functions ) )
		{
			RPCMetaWrapper wrapper;
			if ( functions.Find( funcName, wrapper ) )
			{
				if ( wrapper.GetInstance() )
				{
					auto functionCallData = new Param4< CallType, ParamsReadContext, PlayerIdentity, Object >( CallType.Server, ctx, sender, target );
				
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
			} else
			{
				CF_Log.Warn( recievedFrom + " tried sending " + modName + "::<" + funcName + "> which does not seem to exist!");
			}
		} else
		{
			CF_Log.Warn( recievedFrom + " tried sending <" + modName + ">::" + funcName + " which does not seem to exist!");
		}
	}

	void SendRPC( string modName, string funcName, Param params = NULL, bool guaranteed = false, PlayerIdentity sendToIdentity = NULL, Object sendToTarget = NULL )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_6(this).Add(modName).Add(funcName).Add(params).Add(guaranteed).Add(sendToIdentity).Add(sendToTarget);
		#endif

		auto sendData = new array< ref Param >;
		sendData.Insert( new Param2< string, string >( modName, funcName ) );
		sendData.Insert( params );
		
		//In case we are in the singleplayer and the data is consumed twice for both client and server, we need to add it twice. Better than making a deep copy with more complicated rules on receiving
		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCActions.Contains( modName ) )
			{
				if ( m_RPCActions[ modName ].Contains( funcName ) )
				{
					RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];
					
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
	void SendRPCs( string modName, string funcName, array< ref Param > params, bool guaranteed = false, PlayerIdentity sendToIdentity = NULL, Object sendToTarget = NULL )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_6(this).Add(modName).Add(funcName).Add(params).Add(guaranteed).Add(sendToIdentity).Add(sendToTarget);
		#endif

		params.InsertAt( new Param2< string, string >( modName, funcName ), 0 );

		GetGame().RPC( sendToTarget, FRAMEWORK_RPC_ID, params, guaranteed, sendToIdentity );

		if ( !GetGame().IsMultiplayer() )
		{
			if ( m_RPCActions.Contains( modName ) )
			{
				if ( m_RPCActions[ modName ].Contains( funcName ) )
				{
					RPCMetaWrapper wrapper = m_RPCActions[ modName ][ funcName ];
					
					if ( ( wrapper.GetSPExecutionType() == SingleplayerExecutionType.Both ) )
					{
						CF_Log.Warn( modName + "::" + funcName + " does not support \"SingleplayerExecutionType.Both\" when using RPCManager::SendRPCs, use RPCManager::SendRPC instead!");
					}
				}
			}
		}
	}

	bool AddRPC( string modName, string funcName, Class instance, int singlePlayerExecType = SingleplayerExecutionType.Server )
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_4(this).Add(modName).Add(funcName).Add(instance).Add(singlePlayerExecType);
		#endif

		if ( !m_RPCActions.Contains( modName ) )
		{
			m_RPCActions.Set( modName, new map< string, ref RPCMetaWrapper > );
		}
		
		auto wrapper = new RPCMetaWrapper( instance, singlePlayerExecType );
		
		m_RPCActions[ modName ].Set( funcName, wrapper );

		return true;
	}
};

static ref RPCManager g_RPCManager;

static RPCManager GetRPCManager()
{
	if ( !g_RPCManager )
	{
		g_RPCManager = new RPCManager();
	}

	return g_RPCManager;
}
