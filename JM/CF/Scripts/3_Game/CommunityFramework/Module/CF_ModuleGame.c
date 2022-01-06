class CF_ModuleGame : CF_ModuleCore
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

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

	void OnRPC(CF_ModuleRPC rpc, Serializer ctx);
};

typedef CF_ModuleGame CF_Module;
