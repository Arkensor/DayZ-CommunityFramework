class JMModuleBase : CF_WorldModule
{
	override void OnInit()
	{
		super.OnInit();
	}

	void RegisterKeyMouseBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterKeyMouseBinding", "Bind");
	}

	void RegisterBinding(JMModuleBinding binding) 
	{
		Bind(binding);

		Error_Deprecated("RegisterBinding", "Bind");
	}
};
