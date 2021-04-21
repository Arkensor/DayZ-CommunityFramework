modded class DayZGame
{
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        //Intercept incoming RPCs and consume them if their rpc_type is meant for CF.RPC
        if(CF_RPC._OnRPC(sender, target, rpc_type, ctx)) return;

        super.OnRPC(sender, target, rpc_type, ctx);
    }
}
