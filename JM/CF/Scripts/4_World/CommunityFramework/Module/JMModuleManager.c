

static bool DISABLE_ALL_INPUT = false;

class JMModuleManager: JMModuleManagerBase
{
	protected autoptr map< typename, ref JMModuleBase > m_Modules;

	protected autoptr array< JMModuleBase > m_ModuleList;

	void JMModuleManager()
	{
	}

	void ~JMModuleManager()
	{
	}

	void ConstructModules( JMModuleConstructorBase construct )
	{
		construct.Generate( m_Modules, m_ModuleList );
	}

	ref JMModuleBase GetModule( typename type )
	{
		return m_Modules.Get( type );
	}

	override void Print_DumpModules()
	{
		super.Print_DumpModules();

		Print( "Modules Loaded" );
		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			Print( "" + i + " -> " + m_ModuleList[i].GetModuleName() );
		}
	}

	protected void InitModule( ref JMModuleBase module )
	{
		module.Init();
	}

	override void InitModules()
	{
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
		super.OnClientPermissionsUpdated();
		
		for ( int i = 0; i < m_ModuleList.Count(); i++ )
		{
			m_ModuleList[i].OnClientPermissionsUpdated();
		}
	}

	override void OnInit()
	{
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
	return JMModuleManager.Cast( g_cf_ModuleManager );
}

static void CreateModuleManager( JMModuleConstructorBase construct )
{
	//! Temporary
	CF_CreateWorld();

	ref JMModuleManager manager = new JMModuleManager;

	manager.ConstructModules( construct );
	manager.InitModules();

	g_cf_ModuleManager = manager;
}