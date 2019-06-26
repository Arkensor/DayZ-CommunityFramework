modded class InGameMenu
{
	protected string m_MainLayoutFileLocation = "JM/CF/GUI/layouts/ingamemenu.layout";
	protected string m_ButtonLayoutFileLocation = "JM/CF/GUI/layouts/ingamemenubutton.layout";

	protected int m_StartUserID = 104245;

	protected autoptr array< ref ButtonWidget > m_Buttons = new array< ref ButtonWidget >;
	protected autoptr array< ref InGameMenuButton > m_ButtonHandlers = new array< ref InGameMenuButton >;
	
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
	
	/*
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
	*/
}
