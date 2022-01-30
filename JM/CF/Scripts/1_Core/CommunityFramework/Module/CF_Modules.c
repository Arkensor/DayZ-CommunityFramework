class CF_Modules<Class T>
{
	static T Get()
	{
		typename type = T;
		T module;
		Class.CastTo(module, CF_ModuleCoreManager.s_ModulesMap[type]);
		return module;
	}

	static bool Get(inout T module)
	{
		typename type = T;
		return Class.CastTo(module, CF_ModuleCoreManager.s_ModulesMap[type]);
	}
};
