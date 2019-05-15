modded class InGameMenu
{
	protected string m_MainLayoutFileLocation = "JM/CF/GUI/layouts/ingamemenu.layout";
	protected string m_ButtonLayoutFileLocation = "JM/CF/GUI/layouts/ingamemenubutton.layout";

	protected int m_StartUserID = 104245;

	protected ref array< ref ButtonWidget > m_Buttons = new ref array< ref ButtonWidget >;
	protected ref array< ref InGameMenuButton > m_ButtonHandlers = new ref array< ref InGameMenuButton >;
	
	void InGameMenu()
	{
		RegisterButtons();
	}

	void RegisterButtons()
	{
		RegisterButton( "CREDITS", "OnClick_Credits" );
	}

	InGameMenuButton RegisterButton( string text, string function, int disablewhen = 0, int index = -1 )
	{
		ref InGameMenuButton button = new ref InGameMenuButton( text, function, disablewhen );
		if ( index == -1 )
		{
			m_ButtonHandlers.Insert( button );
		} else 
		{
			m_ButtonHandlers.InsertAt( button, index );
		}

		return button;
	}

	void OnClick_Credits()
	{
		EnterScriptedMenu( MENU_CREDITS );
	}

	override Widget Init()
	{
		m_Root = GetGame().GetWorkspace().CreateWidgets( m_MainLayoutFileLocation );
		
		m_ContinueButton	= m_Root.FindAnyWidget( "continuebtn" );
		m_ExitButton		= m_Root.FindAnyWidget( "exitbtn" );
		m_RestartButton		= m_Root.FindAnyWidget( "restartbtn" );
		m_RestartDeadButton	= m_Root.FindAnyWidget( "restartdeadbtn" );
		m_OptionsButton		= m_Root.FindAnyWidget( "optionsbtn" );
		
		if ( GetGame().IsMultiplayer() && GetGame().IsClient() )
		{
			ButtonSetText( m_RestartButton, "#main_menu_respawn" );
			ButtonSetText( m_RestartDeadButton, "#main_menu_respawn" );
		}
		else
		{
			ButtonSetText( m_RestartButton, "#main_menu_restart" );
			ButtonSetText( m_RestartDeadButton, "#main_menu_restart" );
		}

	#ifdef BULDOZER
		delete m_RestartButton;
	#endif

		HudShow( false );
		
		SetGameVersion();

		ref InGameMenuButton data;
		ButtonWidget button;
		TextWidget text;

		for ( int i = 0; i < m_ButtonHandlers.Count(); i++ )
		{
			data = m_ButtonHandlers.Get( i );

			button = ButtonWidget.Cast( GetGame().GetWorkspace().CreateWidgets( m_ButtonLayoutFileLocation, m_Root.FindAnyWidget( "top" ) ) );
			button.SetUserID( m_StartUserID + i );
			ButtonSetText( button, data.GetText() );
			
/*
			if ( data.DisableWhen() == 2 && !( GetGame().CanRespawnPlayer() || ( player && player.IsUnconscious() ) ) )
			{
				button.Enable(false);
			}

			if ( data.DisableWhen() == 1 && ( GetGame().CanRespawnPlayer() || ( player && player.IsUnconscious() ) ) )
			{
				button.Enable(false);
			}
*/

			m_Buttons.Insert( button );
		}

		return m_Root;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		int id = w.GetUserID() - m_StartUserID;

		if ( id >= 0 && id < m_ButtonHandlers.Count() )
		{
			GetGame().GameScript.CallFunctionParams( this, m_ButtonHandlers[id].GetFunction(), NULL, new Param );
			return true;
		}
		
		if ( w == m_ContinueButton )
		{
			OnClick_Continue();
			return true;
		}
		else if ( w == m_RestartButton || w == m_RestartDeadButton )
		{
			OnClick_Restart();
			return true;
		}
		else if ( w == m_OptionsButton )
		{
			OnClick_Options();
			return true;
		}
		else if ( w == m_ExitButton )
		{
			OnClick_Exit();
			return true;
		}

		return super.OnClick( w, x, y, button );
	}
	
	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		return super.OnModalResult(w, x, y, code, result);
	}

	// 1.02 compat, remove after 1.03 is on stable!
	
	protected void SetGameVersion()
	{
		TextWidget version_widget = TextWidget.Cast( m_Root.FindAnyWidget("version") );
		string version;
		GetGame().GetVersion( version );
		version_widget.SetText( "#main_menu_version" + " " + version );

		#ifdef PREVIEW_BUILD
			version_widget.SetText("THIS IS PREVIEW");
		#endif
	}

	protected void HudShow( bool show )
	{
		Mission mission = GetGame().GetMission();
		if ( mission )
		{
			IngameHud hud = IngameHud.Cast( mission.GetHud() );
			if ( hud )
			{
				hud.ShowHudUI(show);
				hud.ShowQuickbarUI(show);
			}
		}
	}

	override bool OnMouseEnter( Widget w, int x, int y )
	{
		ColorHighlight( w );
		return true;
	}
	
	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		ColorNormal( w );
		return true;
	}
	
	protected void OnClick_Continue()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
	}
	
	protected void OnClick_Restart()
	{
		if ( !GetGame().IsMultiplayer() )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RestartMission);
			GetGame().GetMission().PlayerControlEnable();
		}
		else
		{
			Man player = GetGame().GetPlayer();
			
			if ( player && player.IsUnconscious() )
			{
				GetGame().GetUIManager().ShowDialog("#main_menu_respawn", "#main_menu_respawn_question", IDC_INT_RETRY, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
				GetGame().GetMission().PlayerControlEnable();
			}
			else
			{
				GameRespawn();
			}
		}
	}
	
	protected void OnClick_Options()
	{
		EnterScriptedMenu(MENU_OPTIONS);
	}
	
	protected void OnClick_Exit()
	{
		GetGame().LogoutRequestTime();
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().CreateLogoutMenu, this);
		
		//GetGame().GetUIManager().ShowDialog("EXIT", "Are you sure you want to exit?", IDC_INT_EXIT, DBT_YESNO, DBB_YES, DMT_QUESTION, NULL);
	}
	
	override void Update( float timeslice )
	{
		super.Update( timeslice );
		
		UpdateGUI();
	}
	
	protected void UpdateGUI()
	{
		Man player = GetGame().GetPlayer();
		bool player_is_alive = false;
	
		if (player)
		{
			int life_state = player.GetPlayerState();
	
			if (life_state == EPlayerStates.ALIVE)
			{
				player_is_alive = true;
			}
		}

		if ( GetGame().IsMultiplayer() && GetGame().IsClient() )
		{
			m_ContinueButton.Show( player_is_alive );
			m_RestartButton.Show( (player_is_alive && player.IsUnconscious()) );
			m_RestartDeadButton.Show( !player_is_alive );
		}
		else
		{
			m_ContinueButton.Show( player_is_alive );
			m_RestartButton.Show( (player_is_alive && player.IsUnconscious()) );
			m_RestartDeadButton.Show( !player_is_alive );
		}
	}

	protected void ColorHighlight( Widget w )
	{
		if( !w )
			return;
		
		ButtonSetColor(w, ARGB(255, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 255, 0, 0));
	}
	
	protected void ColorNormal( Widget w )
	{
		if( !w )
			return;
		
		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 255, 255, 255));
	}

	protected void ButtonSetText( Widget w, string text )
	{
		if( !w )
			return;
				
		TextWidget label = TextWidget.Cast(w.FindWidget( w.GetName() + "_label" ) );
		
		if( label )
		{
			label.SetText( text );
		}
	}
	
	protected void ButtonSetColor( Widget w, int color )
	{
		if( !w )
			return;
		
		Widget panel = w.FindWidget( w.GetName() + "_panel" );
		
		if( panel )
		{
			panel.SetColor( color );
		}
	}
	
	protected void ButtonSetTextColor( Widget w, int color )
	{
		if( !w )
			return;

		TextWidget label	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_label" ) );
				
		if( label )
		{
			label.SetColor( color );
		}
	}
}
