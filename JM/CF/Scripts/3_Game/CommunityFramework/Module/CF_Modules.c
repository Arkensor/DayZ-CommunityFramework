class CF_Modules<Class T>
{
	static T Get()
	{
		typename type = T;
		T module;
		Class.CastTo(module, CF_Module_Manager.s_ModuleMap[type]);
		return module;
	}

	static bool Get(T module)
	{
		typename type = T;
		return Class.CastTo(module, CF_Module_Manager.s_ModuleMap[type]);
	}
};
