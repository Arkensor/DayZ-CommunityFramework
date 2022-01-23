class CF_ModuleGame : CF_ModuleCore
{
	const static int NETWORKED_VARIABLES_RPC_ID = 435022;

	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);
	autoptr CF_NetworkedVariables m_CF_NetworkedVariables = new CF_NetworkedVariables(this);

	int m_CF_RPC_Minimum;
	int m_CF_RPC_Maximum;

	void Bind(string function, string input, bool limitMenu = false)
	{
		m_CF_Bindings.Bind(function, input, limitMenu);

		EnableUpdateInput();
	}

	void Bind(string function, UAInput input, bool limitMenu = false)
	{
		m_CF_Bindings.Bind(function, input, limitMenu);

		EnableUpdateInput();
	}

	void Bind(CF_InputBinding binding)
	{
		m_CF_Bindings.Bind(binding);

		EnableUpdateInput();
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
				OnVariablesSynchronized(this, new CF_EventArgs);
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

	void EnableUpdateInput()
	{
		CF_ModuleGameManager.s_UpdateInput.Add(this);
	}

	void OnRPC(Class sender, CF_EventArgs args);

	void OnVariablesSynchronized(Class sender, CF_EventArgs args);
};

typedef CF_ModuleGame CF_Module;
