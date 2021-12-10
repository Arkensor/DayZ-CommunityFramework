

static bool DISABLE_ALL_INPUT = false;

class JMModuleManager: JMModuleManagerBase
{
	protected autoptr map< typename, ref JMModuleBase > m_Modules;

	protected autoptr array< JMModuleBase > m_ModuleList;

	void JMModuleManager()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "JMModuleManager");
		#endif

	}

	void ~JMModuleManager()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "~JMModuleManager");
		#endif

	}

	void ConstructModules( JMModuleConstructorBase construct )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "ConstructModules").Add(construct);
		#endif

		construct.Generate( m_Modules, m_ModuleList );
	}

	ref JMModuleBase GetModule( typename type )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "GetModule").Add(type);
		#endif

		return m_Modules.Get( type );
	}

	override void Print_DumpModules()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "Print_DumpModules");
		#endif

		super.Print_DumpModules();

		Print( "Modules Loaded" );
		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			Print( "" + i + " -> " + m_ModuleList[i].GetModuleName() );
		}
	}

	protected void InitModule( ref JMModuleBase module )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "InitModule").Add(module);
		#endif

		module.Init();
	}

	override void InitModules()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "InitModules");
		#endif

		super.InitModules();
		
		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			InitModule( m_ModuleList[i] );
		}

		Print_DumpModules();

		OnInit();
	}

	override void OnSettingsUpdated()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnSettingsUpdated");
		#endif

		super.OnSettingsUpdated();

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnSettingsUpdated();
			}
		}
	}

	override void OnClientPermissionsUpdated()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnClientPermissionsUpdated");
		#endif

		super.OnClientPermissionsUpdated();
		
		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			m_ModuleList[i].OnClientPermissionsUpdated();
		}
	}

	override void OnInit()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnInit");
		#endif

		super.OnInit();

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnInit();
			}
		}
	}

	override void OnMissionStart()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMissionStart");
		#endif

		super.OnMissionStart();

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMissionStart();
			}
		}
	}

	override void OnMissionFinish()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMissionFinish");
		#endif

		super.OnMissionFinish();

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMissionFinish();
			}
		}
	}

	override void OnMissionLoaded()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMissionLoaded");
		#endif

		super.OnMissionLoaded();

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMissionLoaded();
			}
		}
	}

	override void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_4(this, "OnRPC").Add(sender).Add(target).Add(rpc_type).Add(ctx);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			JMModuleBase module = m_ModuleList[i];

			int min = module.GetRPCMin();
			int max = module.GetRPCMax();

			if ( min == -1 || rpc_type <= min )
				continue;

			if ( max == -1 || rpc_type >= max )
				continue;

			if ( module.IsEnabled() )
			{
				module.OnRPC( sender, target, rpc_type, ctx );
			}

			return;
		}
	}

	override void OnUpdate( float timeslice )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnUpdate").Add(timeslice);
		#endif

		super.OnUpdate( timeslice );
		
		bool inputIsFocused = false;

		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			ref Widget focusedWidget = GetFocus();
			if ( focusedWidget && focusedWidget.ClassName().Contains("EditBoxWidget") )
			{
				inputIsFocused = true;
			}
		}

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			JMModuleBase module = m_ModuleList[i];

			if ( module.IsEnabled() && !module.IsPreventingInput() && !inputIsFocused && !DISABLE_ALL_INPUT && ( GetGame().IsClient() || !GetGame().IsMultiplayer() ) )
			{
				for ( int kb = 0; kb < module.GetBindings().Count(); kb++ )
				{
					JMModuleBinding k_m_Binding = module.GetBindings().Get( kb );

					if ( IsPreventingModuleBindings() || GetGame().GetUIManager().GetMenu() )
					{
						if ( !k_m_Binding.CanBeUsedInMenu() )
						{
							continue;
						}
					}

					string inputName = k_m_Binding.GetUAInputName();

					UAInput input = GetUApi().GetInputByName( inputName );

					bool localPress = input.LocalPress();
					bool localRelease = input.LocalRelease();
					bool localHold = input.LocalHold();
					bool localClick = input.LocalClick();
					bool localDoubleClick = input.LocalDoubleClick();

					bool canLocalPress = input.IsPressLimit();
					bool canLocalRelease = input.IsReleaseLimit();
					bool canLocalHold = input.IsHoldLimit();
					bool canLocalClick = input.IsClickLimit();
					bool canLocalDoubleClick = input.IsDoubleClickLimit();

					bool isLimited = canLocalPress || canLocalRelease || canLocalHold || canLocalClick || canLocalDoubleClick;

					if ( isLimited )
					{
						if ( canLocalPress && localPress )
						{
							GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
						}
						
						if ( canLocalRelease && localRelease )
						{
							GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
						}

						if ( canLocalHold && localHold )
						{
							GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
						}

						if ( canLocalClick && localClick )
						{
							GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
						}

						if ( canLocalDoubleClick && localDoubleClick )
						{
							GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
						}
					} else
					{
						GetGame().GameScript.CallFunctionParams( module, k_m_Binding.GetCallBackFunction(), NULL, new Param1< UAInput >( input ) );
					}
				}
			}
			
			module.OnUpdate( timeslice );
		}
	}

	override void OnWorldCleanup()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnWorldCleanup");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnWorldCleanup();
			}
		}
	}

	override void OnMPSessionStart()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMPSessionStart");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPSessionStart();
			}
		}
	}

	override void OnMPSessionPlayerReady()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMPSessionPlayerReady");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPSessionPlayerReady();
			}
		}
	}

	override void OnMPSessionFail()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMPSessionFail");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPSessionFail();
			}
		}
	}

	override void OnMPSessionEnd()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMPSessionEnd");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPSessionEnd();
			}
		}
	}

	override void OnMPConnectAbort()
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_0(this, "OnMPConnectAbort");
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPConnectAbort();
			}
		}
	}

	override void OnMPConnectionLost( int duration )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnMPConnectionLost").Add(duration);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnMPConnectionLost( duration );
			}
		}
	}

	override void OnRespawn( int time )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnRespawn").Add(time);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnRespawn( time );
			}
		}
	}
	
	void OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_2(this, "OnClientLogoutCancelled").Add(player).Add(identity);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientLogoutCancelled( player, identity );
			}
		}
	}

	void OnInvokeConnect( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_2(this, "OnInvokeConnect").Add(player).Add(identity);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnInvokeConnect( player, identity );
			}
		}
	}

	void OnInvokeDisconnect( PlayerBase player )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnInvokeDisconnect").Add(player);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnInvokeDisconnect( player );
			}
		}
	}

	void OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_4(this, "OnClientNew").Add(player).Add(identity).Add(pos).Add(ctx);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientNew( player, identity, pos, ctx );
			}
		}
	}

	void OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_2(this, "OnClientReady").Add(player).Add(identity);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientReady( player, identity );
			}
		}
	}

	void OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientPrepare").Add(identity).Add(useDB).Add(pos).Add(yaw).Add(preloadTimeout);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout );
			}
		}
	}

	void OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientReconnect").Add(player).Add(identity);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientReconnect( player, identity );
			}
		}
	}

	void OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientRespawn").Add(player).Add(identity);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientRespawn( player, identity );
			}
		}
	}

	void OnClientLogout( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientLogout").Add(player).Add(identity).Add(logoutTime).Add(authFailed);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientLogout( player, identity, logoutTime, authFailed );
			}
		}
	}

	void OnClientDisconnect( PlayerBase player, PlayerIdentity identity, string uid )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientDisconnect").Add(player).Add(identity).Add(uid);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientDisconnect( player, identity, uid );
			}
		}
	}

	void OnClientLogoutCancelled( PlayerBase player )
	{
		#ifdef CF_TRACE_ENABLED
		// auto trace = CF_Trace_1(this, "OnClientLogoutCancelled").Add(player);
		#endif

		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			if ( m_ModuleList[i].IsEnabled() )
			{
				m_ModuleList[i].OnClientLogoutCancelled( player );
			}
		}
	}
}

static ref JMModuleManager GetModuleManager()
{
	#ifdef CF_TRACE_ENABLED
	// auto trace = CF_Trace_0("GetModuleManager");
	#endif

	return JMModuleManager.Cast( g_cf_ModuleManager );
}

static void CreateModuleManager( JMModuleConstructorBase construct )
{
	#ifdef CF_TRACE_ENABLED
	// auto trace = CF_Trace_1("CreateModuleManager").Add(construct);
	#endif

	//! Temporary
	CF_CreateWorld();

	ref JMModuleManager manager = new JMModuleManager;

	manager.ConstructModules( construct );
	manager.InitModules();

	g_cf_ModuleManager = manager;
}