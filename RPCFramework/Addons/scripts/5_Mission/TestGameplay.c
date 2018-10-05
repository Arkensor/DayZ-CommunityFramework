modded class MissionGameplay
{
    ref TestGame m_TestGame;

    void MissionGameplay()
    {
        m_TestGame = new ref TestGame();

        Print( "Loaded TestGameplay");
    }

    override void OnKeyPress( int key )
    {
        super.OnKeyPress( key );

        m_TestGame.OnKeyPress( key );
    }
}