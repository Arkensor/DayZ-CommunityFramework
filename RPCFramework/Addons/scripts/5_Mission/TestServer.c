#ifdef RPCFRAMEWORK_TESTING
modded class MissionServer
{
    ref TestGame m_TestGame;

    void MissionServer()
    {
        m_TestGame = new ref TestGame();

        Print( "Loaded TestServer");
    }
}
#endif