modded class MissionServer
{
    void MissionServer()
    {
        Print( "Loaded TestServer");
        GetRPCManager().AddAction( new RPCTestAction );
    }
}