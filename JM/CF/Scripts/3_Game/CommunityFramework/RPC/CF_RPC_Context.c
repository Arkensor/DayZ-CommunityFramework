class CF_RPC_Context : ScriptRPC
{
	private bool m_Guaranteed;
	private Object m_Target;

	private void CF_RPC_Context(Object target = null, bool guaranteed = false)
	{
		m_Target = target;
		m_Guaranteed = guaranteed;
	}

	static ref CF_RPC_Context Prepare(string modName, string funcName, Object target = null, bool guaranteed = false)
	{
		CF_RPC_Context ctx(target, guaranteed);
		ctx.Write(modName);
		ctx.Write(funcName);
		return ctx;
	}

	void Post(PlayerIdentity recipient = null)
	{
		//! temp hardcode of id for POC
		Send(m_Target, 10042, m_Guaranteed, recipient);
	}
};