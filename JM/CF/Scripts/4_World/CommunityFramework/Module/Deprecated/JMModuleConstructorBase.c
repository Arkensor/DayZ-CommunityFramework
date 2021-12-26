class JMModuleConstructorBase
{
	void JMModuleConstructorBase()
	{
		TTypenameArray modules = new TTypenameArray();
		Print(modules);
		RegisterModules(modules);
		Print(modules);
		for (int i = 0; i < modules.Count(); i++)
		{
			CF_ModuleCoreManager._Insert(modules[i]);
		}
	}

	void RegisterModules(out TTypenameArray modules);
};
