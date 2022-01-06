/**
 * @class JMModuleConstructorBase
 * 
 * @deprecated
 */
class JMModuleConstructorBase
{
	autoptr TTypenameArray m_Modules = new TTypenameArray();

	void JMModuleConstructorBase()
	{
		RegisterModules(m_Modules);
		for (int i = 0; i < m_Modules.Count(); i++)
		{
			CF_ModuleCoreManager._Insert(m_Modules[i]);
		}
	}

	void RegisterModules(out TTypenameArray modules);
};
