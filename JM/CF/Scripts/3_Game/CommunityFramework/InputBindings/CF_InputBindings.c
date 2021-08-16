class CF_InputBindings
{
	ref CF_InputBinding m_Head;

	Class m_Instance;

	void CF_InputBindings(Class instance)
	{
		m_Instance = instance;
	}

	/**
	 * Binds input to head, pushes other entries back
	 */
	void Bind(string callback, string input)
	{
		Bind(callback, GetUApi().GetInputByName(input));
	}

	/**
	 * Binds input to head, pushes other entries back
	 */
	void Bind(string callback, UAInput input)
	{
		CF_InputBinding binding = new CF_InputBinding();
		binding.m_Function = callback;
		binding.m_Input = input;

		Bind(binding);
	}

	/**
	 * Binds input to head, pushes other entries back
	 */
	void Bind(CF_InputBinding binding)
	{
		if (m_Head) binding.m_Next = m_Head;
		m_Head = binding;
	}

	void Update(float dt)
	{
		CF_InputBinding binding = m_Head;
		while (binding)
		{
			UAInput input = binding.m_Input;
			bool isModified = input.LocalValue() != 0.0 || input.LocalRelease();

			if (input.IsLimited())
			{
				if (isModified)
				{
					g_Script.CallFunctionParams(m_Instance, binding.m_Function, NULL, new Param1<UAInput>(binding.m_Input));
				}
			}
			else if (isModified)
			{
				g_Script.CallFunctionParams(m_Instance, binding.m_Function, NULL, new Param1<UAInput>(binding.m_Input));
			}

			binding = binding.m_Next;
		}
	}
};
