class CF_Module_Register
{
	void CF_Module_Register()
	{
		Register();

		array<typename> modules = new array<typename>();
		RegisterModules(modules);
		for (int i = 0; i < modules.Count(); i++) CF_Module_Manager.RegisterModule(modules[i]);
	}

	void Register();

	void RegisterModules(out array<typename> modules);
};

/**
 * @brief Deprecated, just call the constructor
 */
static void CreateModuleManager(CF_Module_Register register)
{
}