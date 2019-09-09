class JMModuleManager: JMModuleManagerBase
{
	protected autoptr map< typename, ref JMModuleBase > m_Modules;

	void JMModuleManager()
	{
		GetLogger().Log( "JMModuleManager::JMModuleManager()", "JM_COT_ModuleFramework" );
	}

	void ~JMModuleManager()
	{
		GetLogger().Log( "JMModuleManager::~JMModuleManager()", "JM_COT_ModuleFramework" );
	}

	void ConstructModules( JMModuleConstructorBase construct )
	{
		construct.Generate( m_Modules );
	}

	protected void RegisterModule( ref JMModuleBase module )
	{
		module.Init();
	}

	ref JMModuleBase GetModule( typename type )
	{
		return m_Modules.Get( type );
	}

	override void Print_DumpModules()
	{
		super.Print_DumpModules();

		Print( "Modules Loaded" );
		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			Print( "" + i + " -> " + m_Modules.GetElement( i ).GetModuleName() );
		}
	}

	override void RegisterModules()
	{
		super.RegisterModules();

		GetLogger().Log( "JMModuleManager::RegisterModules()", "JM_COT_ModuleFramework" );
        
		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			RegisterModule( m_Modules.GetElement( i ) );
		}

		Print_DumpModules();
	}

	override void OnSettingsUpdated()
	{
		super.OnSettingsUpdated();

		GetLogger().Log( "JMModuleManager::OnSettingsUpdated()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() )
			{
				m_Modules.GetElement( i ).OnSettingsUpdated();
			}
		}
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetLogger().Log( "JMModuleManager::OnMissionStart()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() )
			{
				m_Modules.GetElement( i ).OnMissionStart();
			}
		}
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetLogger().Log( "JMModuleManager::OnMissionFinish()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() )
			{
				m_Modules.GetElement( i ).OnMissionFinish();
			}
		}
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		GetLogger().Log( "JMModuleManager::OnMissionLoaded()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() )
			{
				m_Modules.GetElement( i ).OnMissionLoaded();
			}
		}
	}

	override void OnUpdate( float timeslice )
	{
		super.OnUpdate( timeslice );
		
		GetLogger().Log( "JMModuleManager::OnUpdate()", "JM_COT_ModuleFramework" );

		bool inputIsFocused = false;

		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			ref Widget focusedWidget = GetFocus();
			if ( focusedWidget && focusedWidget.ClassName().Contains("EditBoxWidget") )
			{
				inputIsFocused = true;
			}
		}

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			JMModuleBase module = m_Modules.GetElement( i );

			if ( module.IsEnabled() && !module.IsPreventingInput() && ( GetGame().IsClient() || !GetGame().IsMultiplayer() ) )
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

					if ( DISABLE_ALL_INPUT || inputIsFocused )
					{
						continue;
					}

					UAInput input = GetUApi().GetInputByName( k_m_Binding.GetUAInputName() );

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

	override bool OnWorldCleanup()
	{
		if ( super.OnWorldCleanup() )
			return true;

		GetLogger().Log( "JMModuleManager::OnWorldCleanup()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnWorldCleanup() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPSessionStart()
	{
		if ( super.OnMPSessionStart() )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPSessionStart()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPSessionStart() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPSessionPlayerReady()
	{
		if ( super.OnMPSessionPlayerReady() )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPSessionPlayerReady()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPSessionPlayerReady() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPSessionFail()
	{
		if ( super.OnMPSessionFail() )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPSessionFail()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPSessionFail() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPSessionEnd()
	{
		if ( super.OnMPSessionEnd() )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPSessionEnd()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPSessionEnd() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPConnectAbort()
	{
		if ( super.OnMPConnectAbort() )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPConnectAbort()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPConnectAbort() )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnMPConnectionLost( int duration )
	{
		if ( super.OnMPConnectionLost( duration ) )
			return true;

		GetLogger().Log( "JMModuleManager::OnMPConnectionLost()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnMPConnectionLost( duration ) )
			{
				return true;
			}
		}

		return false;
	}

	override bool OnRespawn( int time )
	{
		if ( super.OnRespawn( time ) )
			return true;

		GetLogger().Log( "JMModuleManager::OnRespawn()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnRespawn( time ) )
			{
				return true;
			}
		}

		return false;
	}
	
	bool OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientLogoutCancelled()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientLogoutCancelled( player, identity ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		GetLogger().Log( "JMModuleManager::OnClientNew()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientNew( player, identity, pos, ctx ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientReady()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientReady( player, identity ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		GetLogger().Log( "JMModuleManager::OnClientPrepare()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientReconnect()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientReconnect( player, identity ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientRespawn()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientRespawn( player, identity ) )
			{
				return true;
			}
		}

		return false;
	}

	bool OnClientDisconnected( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
		GetLogger().Log( "JMModuleManager::OnClientDisconnected()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).IsEnabled() && m_Modules.GetElement( i ).OnClientDisconnected( player, identity, logoutTime, authFailed ) )
			{
				return true;
			}
		}

		return false;
	}
}

static ref JMModuleManager GetModuleManager()
{
	return JMModuleManager.Cast( g_cot_ModuleManager );
}

static void CreateModuleManager( JMModuleConstructorBase construct )
{
	g_cot_ModuleManager = new JMModuleManager;
	JMModuleManager manager;
	if ( Class.CastTo( manager, g_cot_ModuleManager) )
	{
		manager.ConstructModules( construct );
		manager.RegisterModules();
	}
}