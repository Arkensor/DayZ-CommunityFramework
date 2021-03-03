class JMVariableBindingBase
{
	static const int JM_VARIABLE_UPDATE = 435022;
	
	protected string m_VariableName;
	
	void JMVariableBindingBase(string variable_name)
	{
		m_VariableName = variable_name;
	}
	
	void UpdateClient(PlayerIdentity client, JMModuleBase instance, bool gauranteed = true);
	
	string GetVariableName()
	{
		return m_VariableName;
	}
}

class JMVariableBinding<Class T>
{	
	override void UpdateClient(PlayerIdentity client, JMModuleBase instance, bool gauranteed = true)
	{
		T variable;
		EnScript.GetClassVar(instance, m_VariableName, 0, variable);
		ScriptRPC rpc = new ScriptRPC();
		rpc.Write(m_VariableName);
		rpc.Write(variable);
		rpc.Send(null, JM_VARIABLE_UPDATE, gauranteed, client);
	}
}