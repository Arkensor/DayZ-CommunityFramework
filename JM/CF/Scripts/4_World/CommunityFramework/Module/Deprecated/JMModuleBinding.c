/**
 * @class JMModuleBinding
 * 
 * @deprecated
 */
class JMModuleBinding : CF_InputBinding
{
	void JMModuleBinding(string callback, string input, bool menu = false)
	{
		m_Function = callback;
		m_Input = GetUApi().GetInputByName(input);
		m_LimitMenu = !menu;
	}
};
