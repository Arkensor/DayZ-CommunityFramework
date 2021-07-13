class CF_RPC_HandlerBase
{
    void CF_RPC_HandlerBase()
    {
        CF_RPC.RegisterHandler(this);
    }

    void ~CF_RPC_HandlerBase()
    {
        CF_RPC.UnregisterHandler(this);
    }
}
