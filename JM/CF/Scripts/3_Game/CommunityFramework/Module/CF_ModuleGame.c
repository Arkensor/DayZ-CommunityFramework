class CF_ModuleGame : CF_ModuleCore
{
	const static int NETWORKED_VARIABLES_RPC_ID = 435022;

	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);
	autoptr CF_NetworkedVariables m_CF_NetworkedVariables = new CF_NetworkedVariables(this);

	int m_CF_RPC_Minimum;
	int m_CF_RPC_Maximum;

	/**
	 * @brief Binds a module function to an input
	 * 
	 * @param callback The function within 'm_Instance' to call
	 * @param input The name of the input
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	override void OnInit()
	 *	{
	 *		super.OnInit();
	 * 
	 *		Bind("Close", "UAUIBack", false);
	 *	};
	 * @endcode
	 */
	void Bind(string function, string input, bool limitMenu = false)
	{
		m_CF_Bindings.Bind(function, input, limitMenu);
	}

	/**
	 * @brief Binds a module function to an input
	 * 
	 * @param callback The function within 'm_Instance' to call
	 * @param input The ID of the input. All inputs found within modded inputs is generated as a global int variable of the same name.
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	override void OnInit()
	 *	{
	 *		super.OnInit();
	 * 
	 *		Bind("Close", UAUIBack, false);
	 *	};
	 * @endcode
	 */
	void Bind(string function, int input, bool limitMenu = false)
	{
		m_CF_Bindings.Bind(function, input, limitMenu);
	}

	/**
	 * @brief Binds a module function to an input
	 * 
	 * @param callback The function within 'm_Instance' to call
	 * @param input The name of the input
	 * @param preventCallInMenu If the binding can be called while a menu is open
	 * 
	 * @code
	 *	override void OnInit()
	 *	{
	 *		super.OnInit();
	 * 
	 *		Bind("Close", "UAUIBack", false);
	 *	};
	 * @endcode
	 */
	void Bind(string function, UAInput input, bool limitMenu = false)
	{
		m_CF_Bindings.Bind(function, input, limitMenu);
	}

	/**
	 * @brief Binds a module function to an input
	 * 
	 * @param binding The instance of the binding to add to the list
	 * 
	 * @code
	 *	override void OnInit()
	 *	{
	 *		super.OnInit();
	 * 
	 *		CF_InputBinding binding = new CF_InputBinding();
	 *		binding.m_Function = "Close";
	 *		binding.m_Input = GetUApi().GetInputByID(UAUIBack);
	 *		binding.m_LimitMenu = false;
	 *		
	 *		Bind(binding);
	 *	};
	 * @endcode
	 */
	void Bind(CF_InputBinding binding)
	{
		m_CF_Bindings.Bind(binding);
	}

	/**
	 * @brief Registers functions into legacy RPCFramework
	 */
	void AddLegacyRPC(string funcName, int singlePlayerExecType = SingleplayerExecutionType.Server)
	{
		GetRPCManager().AddRPC(ClassName(), funcName, this, singlePlayerExecType);
	}
	
	/**
	 * @note Only call in 'OnInit'
	 */
	bool RegisterNetSyncVariable(string name)
	{
		return m_CF_NetworkedVariables.Register(name);
	}
	
	void SetSynchDirty()
	{
		// Only the server can send data
		if (!GetGame().IsDedicatedServer())
		{
			// No need to serialize in offline mode, just directly call 'OnVariablesSynchronized'
			if (GetGame().IsServer())
			{
				OnVariablesSynchronized(this, CF_EventArgs.Empty);
			}

			return;
		}

		ScriptRPC rpc = new ScriptRPC();

		rpc.Write(ClassName());

		m_CF_NetworkedVariables.Write(rpc);

		rpc.Send(null, CF_ModuleGame.NETWORKED_VARIABLES_RPC_ID, true, null);
	}

	int GetRPCMin()
	{
		return -1;
	}

	int GetRPCMax()
	{
		return -1;
	}

	void EnableRPC()
	{
		m_CF_RPC_Minimum = GetRPCMin();
		m_CF_RPC_Maximum = GetRPCMax();

		if (m_CF_RPC_Minimum == -1 || m_CF_RPC_Maximum == -1)
		{
			return;
		}

		CF_ModuleGameManager.s_RPC.Add(this);
	}

	/**
	 * @deprecated
	 */
	void EnableUpdateInput();

	void OnRPC(Class sender, CF_EventArgs args);

	void OnVariablesSynchronized(Class sender, CF_EventArgs args);
};

typedef CF_ModuleGame CF_Module;
