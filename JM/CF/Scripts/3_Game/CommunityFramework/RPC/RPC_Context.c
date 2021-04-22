class CF_RPC_Context extends ScriptRPC
{
	protected string m_HandlerType;
	protected string m_FunctionName;
	protected bool m_Guaranteed;
	protected Object m_Target;

    /**
     * @brief Sends the prepared RPC context to the recipient machine. You can re-send the RPC to the same or a different recipient by calling SendTo() again.
     * @code
     * auto rpc = CF.RPC.Prepare("MyHandler", "MyFunction", true);
     * rpc.SendTo(player.GetIdentity());
     * rpc.SendTo(player2.GetIdentity());
     * @endcode
     *
     *
     * @param recipient (Optional) PlayerIdentity of the receiving machine. When used on the client it can only target the server (NULL). NULL when sent from the server targets ALL players.
     * @return bool     Returns true if successfully registered, false otherwise (see script log for details).
     */
    void SendTo(PlayerIdentity recipient = NULL)
    {
        Send(m_Target, CF_RPC.CF_RPC_SCRIPT_ID, m_Guaranteed, recipient);
    }

    /**
     * @brief Resets the written data in the RPC context so it can be sent again with new data.
     * @code
     * auto rpc = CF.RPC.Prepare("MyHandler", "MyFunction", true);
     * rpc.Write("My data");
     * rpc.SendTo(...);
     * rpc.ResetData();
     * rpc.Write("My new data");
     * rpc.SendTo(...);
     * @endcode
     *
     * @return void
     */
    void ResetData()
    {
        Reset();
        Write(m_HandlerType);
        Write(m_FunctionName);
    }

    /**
     * @brief [Internal] Prepares a new RPC context. Used by CF.RPC.Prepare()
     *
     * @return CF_RPC_Context RPC write and send context.
     */
    static ref CF_RPC_Context _Prepare(string handlerType, string functionName, bool guaranteed, Object target = NULL)
    {
        CF_RPC_Context ctx();
        ctx.m_HandlerType = handlerType;
        ctx.m_FunctionName = functionName;
        ctx.m_Guaranteed = guaranteed;
        ctx.m_Target = target;

        ctx.Write(handlerType);
        ctx.Write(functionName);

        return ctx;
    }
}
