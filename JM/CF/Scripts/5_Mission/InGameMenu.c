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
		RegisterButton( "#main_menu_continue", "ContinueMission" );
		RegisterButton( "#main_menu_exit", "QuitMission" );

        if ( GetGame().IsMultiplayer() )
        {
		    RegisterButton( "#main_menu_respawn", "RespawnMission", 2 );
        } else
        {
		    RegisterButton( "#main_menu_restart", "RestartMission" );
        }

		RegisterButton( "#layout_xbox_ingame_menu_options", "EnterOptionsMenu" );

		RegisterButton( "CREDITS", "EnterCreditsMenu" );
    }

    ref InGameMenuButton RegisterButton( string text, string function, int disablewhen = 0, int index = -1 )
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
    
    void ContinueMission()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
	}

	void QuitMission()
	{
		GetGame().LogoutRequestTime();

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().CreateLogoutMenu, this);
	}

	void EnterOptionsMenu()
	{
		EnterScriptedMenu(MENU_OPTIONS);
	}

    void EnterCreditsMenu()
    {
		EnterScriptedMenu(MENU_CREDITS);
    }

    void RestartMission()
    {
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RestartMission);
		GetGame().GetMission().PlayerControlEnable();
    }

	void RespawnMission()
	{
		GetGame().GetUIManager().ShowDialog("#main_menu_respawn", "#main_menu_respawn_question", IDC_INT_RETRY, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
		GetGame().GetMission().PlayerControlEnable();
	}

	override Widget Init()
	{
        layoutRoot = super.Init();

        if (m_ButtonHandlers.Count() == 0) return layoutRoot;

        m_Buttons.Clear();

	 	m_ContinueButton.Unlink();
	 	m_ExitButton.Unlink();
	 	m_RestartButton.Unlink();
	 	m_OptionsButton.Unlink();
        layoutRoot.Unlink();

		layoutRoot = GetGame().GetWorkspace().CreateWidgets( m_MainLayoutFileLocation );
				
		TextWidget version_widget = TextWidget.Cast( layoutRoot.FindAnyWidget("version") );

        string version;
		GetGame().GetVersion( version );
		#ifdef PLATFORM_CONSOLE
			version = "#main_menu_version" + " " + version + " (" + g_Game.GetDatabaseID() + ")";
		#else
			version = "#main_menu_version" + " " + version;
		#endif
		version_widget.SetText( version );

		#ifdef PREVIEW_BUILD
			version_widget.SetText("THIS IS PREVIEW");
		#endif
        
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
        Mission mission = GetGame().GetMission();
		if ( mission )
		{
			IngameHud hud = IngameHud.Cast( mission.GetHud() );
			if ( hud )
			{
				hud.ToggleHud( false, true );
				hud.ToggleQuickBar( false, true );
			}
		}

		m_Buttons.Insert( ButtonWidget.Cast( layoutRoot.FindAnyWidget( "bottom_button" ) ) );
        m_Buttons[0].SetText( m_ButtonHandlers[0].GetText() );
        m_Buttons[0].SetUserID( m_StartUserID );

        if ( m_ButtonHandlers.Count() > 1 )
        {
            ref InGameMenuButton data;
		    ButtonWidget button;

            for ( int i = 1; i < m_ButtonHandlers.Count(); i++ )
			{
				data = m_ButtonHandlers.Get( i );

				button = ButtonWidget.Cast( GetGame().GetWorkspace().CreateWidgets( m_ButtonLayoutFileLocation, layoutRoot.FindAnyWidget( "top_buttons" ) ) );

				button.SetUserID( m_StartUserID + i );
				button.SetText( data.GetText() );

                if ( data.DisableWhen() == 2 && !( GetGame().CanRespawnPlayer() || ( player && player.IsUnconscious() ) ) )
                {
			        button.Enable(false);
                }

                if ( data.DisableWhen() == 1 && ( GetGame().CanRespawnPlayer() || ( player && player.IsUnconscious() ) ) )
                {
			        button.Enable(false);
                }

				m_Buttons.Insert( button );
			}
        }

		return layoutRoot;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		int id = w.GetUserID() - m_StartUserID;

		if ( id >= 0 && id < m_ButtonHandlers.Count() )
		{
		    GetGame().GameScript.CallFunctionParams( this, m_ButtonHandlers[id].GetFunction(), NULL, new Param );
			return true;
		}

		return false;
	}
	
	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		super.OnModalResult(w, x, y, code, result);
	
		return false;
	}
	
	override bool OnMouseEnter( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorWhite( w, enterW );
			return true;
		}
		return false;
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnFocusLost( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorWhite( w, null );
			return true;
		}
		return false;
	}
	
	override bool IsFocusable( Widget w )
	{
		if( w && w.GetUserID() > m_StartUserID )
        {
            return true;
		}

		return false;
	}
	
	//Coloring functions (Until WidgetStyles are useful)
	override void ColorRed( Widget w )
	{
		SetFocus( w );
		
		ButtonWidget button = ButtonWidget.Cast( w );
		if( button && button.GetUserID() > m_StartUserID )
		{
			button.SetTextColor( ARGB( 255, 200, 0, 0 ) );
		}
	}
	
	override void ColorWhite( Widget w, Widget enterW )
	{
		#ifdef PLATFORM_WINDOWS
		SetFocus( null );
		#endif
		
		ButtonWidget button = ButtonWidget.Cast( w );
		if( button && button.GetUserID() > m_StartUserID )
		{
			button.SetTextColor( ARGB( 255, 255, 255, 255 ) );
		}
	}
}
