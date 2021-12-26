class JMModuleManager : JMModuleManagerBase
{
	ref JMModuleBase GetModule(typename type)
	{
		return JMModuleBase.Cast(CF_ModuleCoreManager.Get(type));
	}
}

static JMModuleManager GetModuleManager()
{
	if (!g_JMModuleManager)
	{
		g_JMModuleManager = new JMModuleManager();
	}

	return g_JMModuleManager;
}

static ref JMModuleManager g_JMModuleManager;

static void CreateModuleManager(JMModuleConstructorBase construct)
{
}
