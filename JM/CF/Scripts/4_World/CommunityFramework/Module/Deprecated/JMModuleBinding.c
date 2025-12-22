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
		m_InputID = GetUApi().GetInputByName(input).ID();
		m_LimitMenu = !menu;
	}
};
