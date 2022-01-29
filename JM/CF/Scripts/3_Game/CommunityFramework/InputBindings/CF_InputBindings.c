class CF_InputBindings
{
	static ref array<CF_InputBindings> s_All = new array<CF_InputBindings>();

	ref CF_InputBinding m_Head;
	Class m_Instance;

	/**
	 * @brief Constructor. Adds to the list of all input binding managers. Should be called on parent class construction
	 * 
	 * @param instance The input binding parent
	 */
	void CF_InputBindings(Class instance)
	{
		m_Instance = instance;

		s_All.Insert(this);
	}

	/**
	 * @brief Removes from the list of all input binding managers. Should be called on parent class deletion
	 */
	void ~CF_InputBindings()
	{
		s_All.RemoveItemUnOrdered(this);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 * 
	 * @param callback The function the input binding parent to call
	 * @param input The name of the input
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	bindings.Bind("Close", "UAUIBack", false);
	 * @endcode
	 */
	void Bind(string callback, string input, bool preventCallInMenu = false)
	{
		Bind(callback, GetUApi().GetInputByName(input), preventCallInMenu);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 * 
	 * @param callback The function the input binding parent to call
	 * @param input The ID of the input. All inputs found within modded inputs is generated as a global int variable of the same name
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	bindings.Bind("Close", UAUIBack, false);
	 * @endcode
	 */
	void Bind(string callback, int input, bool preventCallInMenu = false)
	{
		Bind(callback, GetUApi().GetInputByID(input), preventCallInMenu);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 * 
	 * @param callback The function the input binding parent to call
	 * @param input The instance of the input
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	bindings.Bind("Close", GetUApi().GetInputByID(UAUIBack), false);
	 * @endcode
	 */
	void Bind(string callback, UAInput input, bool preventCallInMenu = false)
	{
		CF_InputBinding binding = new CF_InputBinding();
		binding.m_Function = callback;
		binding.m_Input = input;
		binding.m_LimitMenu = preventCallInMenu;

		Bind(binding);
	}

	/**
	 * @brief Binds input to head, pushes other entries back
	 * 
	 * @param binding The instance of the binding to add to the list
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

	/**
	 * @brief Checks for all input state changes and calls the necessary functions
	 * 
	 * @param dt Unused.
	 */
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
