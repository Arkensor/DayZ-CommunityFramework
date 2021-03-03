class JMVariableBindingBase
{
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
	static const int JM_VARIABLE_UPDATE = 435022;
	
	override void UpdateClient(PlayerIdentity client, JMModuleBase instance, bool gauranteed = true)
	{
		T variable;
		EnScript.GetClassVar(instance, m_VariableName, 0, variable);
		
		GetGame().RPCSingleParam(null, JM_VARIABLE_UPDATE, new Param1<T>(variable), gauranteed, client);
	}
}