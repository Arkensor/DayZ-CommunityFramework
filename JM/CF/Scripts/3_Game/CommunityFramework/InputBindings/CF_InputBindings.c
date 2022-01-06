class CF_InputBindings
{
	ref CF_InputBinding m_Head;

	Class m_Instance;

	void CF_InputBindings(Class instance)
	{
		m_Instance = instance;
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 */
	void Bind(string callback, string input, bool limitMenu = false)
	{
		Bind(callback, GetUApi().GetInputByName(input), limitMenu);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 */
	void Bind(string callback, UAInput input, bool limitMenu = false)
	{
		CF_InputBinding binding = new CF_InputBinding();
		binding.m_Function = callback;
		binding.m_Input = input;
		binding.m_LimitMenu = limitMenu;

		Bind(binding);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 */
	void Bind(CF_InputBinding binding)
	{
		if (m_Head)
		{
			binding.m_Next = m_Head;
		}

		m_Head = binding;
		m_Head.UpdateLimits();
	}

	void Update(float dt)
	{
		bool inMenu = GetGame().GetUIManager().GetMenu() || CF_ModuleGame.s_PreventInput;

		CF_InputBinding binding = m_Head;
		while (binding)
		{
			if (!inMenu || (inMenu && !binding.m_LimitMenu))
			{
				UAInput input = binding.m_Input;
				bool isModified = input.LocalValue() != 0.0 || input.LocalRelease();

				if (binding.m_InputLimits != 0)
				{
					if (isModified)
					{
						g_Script.CallFunctionParams(m_Instance, binding.m_Function, NULL, new Param1<UAInput>(input));
					}
				}
				else if (isModified)
				{
					g_Script.CallFunctionParams(m_Instance, binding.m_Function, NULL, new Param1<UAInput>(input));
				}
			}

			binding = binding.m_Next;
		}
	}
};
