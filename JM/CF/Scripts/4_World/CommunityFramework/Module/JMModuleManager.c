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

	}

	ref JMModuleBase GetModule( typename type )
	{
		return m_Modules.Get( type );
	}

	override void RegisterModules()
	{
		super.RegisterModules();

		GetLogger().Log( "JMModuleManager::RegisterModules()", "JM_COT_ModuleFramework" );
        
		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			RegisterModule( m_Modules.GetElement( i ) );
		}
	}

	override void ReloadSettings()
	{
		super.ReloadSettings();

		GetLogger().Log( "JMModuleManager::ReloadSettings()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			m_Modules.GetElement( i ).ReloadSettings();
		}
	}

	override void OnInit()
	{
		super.OnInit();

		GetLogger().Log( "JMModuleManager::OnInit()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			m_Modules.GetElement( i ).Init();
		}
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetLogger().Log( "JMModuleManager::OnMissionStart()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			m_Modules.GetElement( i ).OnMissionStart();
		}
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetLogger().Log( "JMModuleManager::OnMissionFinish()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			m_Modules.GetElement( i ).OnMissionFinish();
		}
	}

	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();

		GetLogger().Log( "JMModuleManager::OnMissionLoaded()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			m_Modules.GetElement( i ).OnMissionLoaded();
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

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			JMModuleBase module = m_Modules.GetElement( i );

			if ( !module.IsPreventingInput() && ( GetGame().IsClient() || !GetGame().IsMultiplayer() ) )
			{
				for ( int kb = 0; kb < module.GetBindings().Count(); kb++ )
				{
					JMModuleBinding k_m_Binding = module.GetBindings().Get( kb );

					if ( GetCommunityOnlineToolsBase().IsOpen() || GetGame().GetUIManager().GetMenu() )
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
	
	void OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientLogoutCancelled()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientLogoutCancelled( player, identity ) )
			{
				break;
			}
		}
	}

	bool OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
		GetLogger().Log( "JMModuleManager::OnClientNew()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientNew( player, identity, pos, ctx ) )
			{
				return true;
			}
		}

		return false;
	}

	void OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientReady()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientReady( player, identity ) )
			{
				break;
			}
		}
	}

	void OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
		GetLogger().Log( "JMModuleManager::OnClientPrepare()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientPrepare( identity, useDB, pos, yaw, preloadTimeout ) )
			{
				break;
			}
		}
	}

	void OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientReconnect()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientReconnect( player, identity ) )
			{
				break;
			}
		}
	}

	void OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
		GetLogger().Log( "JMModuleManager::OnClientRespawn()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientRespawn( player, identity ) )
			{
				break;
			}
		}
	}

	void OnClientDisconnected( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
		GetLogger().Log( "JMModuleManager::OnClientDisconnected()", "JM_COT_ModuleFramework" );

		for ( int i = 0; i < m_Modules.Count(); i++ )
		{
			if ( m_Modules.GetElement( i ).OnClientDisconnected( player, identity, logoutTime, authFailed ) )
			{
				break;
			}
		}
	}
}

static ref JMModuleManager GetModuleManager()
{
	return JMModuleManager.Cast( g_cot_ModuleManager );
}

static void CreateModuleManager()
{
	g_cot_ModuleManager = new JMModuleManager;
}

static void DestroyModuleManager()
{
	delete g_cot_ModuleManager;
}