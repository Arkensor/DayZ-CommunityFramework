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

	void OnClick_Credits()
	{
		EnterScriptedMenu( MENU_CREDITS );
	}

	override Widget Init()
	{
		m_Root = super.Init();
		m_Buttons.Clear();
		m_Root.Unlink();

		m_Root = GetGame().GetWorkspace().CreateWidgets( m_MainLayoutFileLocation );
		
		m_ContinueButton	= m_Root.FindAnyWidget( "continuebtn" );
		m_ExitButton		= m_Root.FindAnyWidget( "exitbtn" );
		m_RestartButton		= m_Root.FindAnyWidget( "restartbtn" );
		m_RestartDeadButton	= m_Root.FindAnyWidget( "restartdeadbtn" );
		m_OptionsButton		= m_Root.FindAnyWidget( "optionsbtn" );
		
		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}

	#ifdef BULDOZER		
		delete m_RestartButton;
	#endif

		HudSow( false );
		
		SetGameVersion();

		if ( m_ButtonHandlers.Count() > 0 )
		{
			ref InGameMenuButton data;
			ButtonWidget button;
			TextWidget text;

			for ( int i = 0; i < m_ButtonHandlers.Count(); i++ )
			{
				data = m_ButtonHandlers.Get( i );

				button = ButtonWidget.Cast( GetGame().GetWorkspace().CreateWidgets( m_ButtonLayoutFileLocation, m_Root.FindAnyWidget( "top" ) ) );
				text = TextWidget.Cast( button.FindAnyWidget( "button_label" ) );

				button.SetUserID( m_StartUserID + i );
				text.SetText( data.GetText() );
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

		return super.OnClick(w, x, y, button);
	}
	
	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		return super.OnModalResult(w, x, y, code, result);
	}
}
