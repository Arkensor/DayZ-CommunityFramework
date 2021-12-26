class CF_ModuleGame : CF_ModuleCore
{
	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);

	int m_CF_RPC_Minimum;
	int m_CF_RPC_Maximum;

	void Bind(string function, string input)
	{
		m_CF_Bindings.Bind(function, input);

		EnableUpdate();
	}

	void Bind(string function, UAInput input)
	{
		m_CF_Bindings.Bind(function, input);

		EnableUpdate();
	}

	void Bind(CF_InputBinding binding)
	{
		m_CF_Bindings.Bind(binding);

		EnableUpdate();
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

	void OnRPC(CF_ModuleRPC rpc, Serializer ctx);

	/**
	 * @note Automatically registers when 'Bind' is called
	 */
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		if (!s_PreventInput)
		{
			m_CF_Bindings.Update(timeslice);
		}
	}
};

typedef CF_ModuleGame CF_Module;
