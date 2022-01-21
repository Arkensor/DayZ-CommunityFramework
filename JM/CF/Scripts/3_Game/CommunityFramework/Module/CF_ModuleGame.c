class CF_ModuleGame : CF_ModuleCore
{
	const static int NETWORKED_VARIABLES_RPC_ID = 435022;

	autoptr CF_InputBindings m_CF_Bindings = new CF_InputBindings(this);
	autoptr CF_NetworkedVariables m_CF_NetworkedVariables = new CF_NetworkedVariables(this);

	int m_CF_RPC_Minimum;
	int m_CF_RPC_Maximum;
	
	void ~CF_ModuleGame()
	{
#ifndef SERVER
		CF_MVVM.Destroy(this);
#endif
	}
	
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
	
	void Open(Widget parent = null)
	{
		string layout = GetLayoutFile();
		if (layout == string.Empty) return;

		CF_MVVM.Create(this, layout, parent);
	}

	void Close()
	{
		CF_MVVM.Destroy(this);
	}

	void NotifyPropertyChanged(string property, CF_EventArgs args = null)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "NotifyPropertyChanged").Add(property).Add(args);
#endif

		CF_MVVM.NotifyPropertyChanged(this, property, args);
	}

	void NotifyPropertyChanged()
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_0(this, "NotifyPropertyChanged");
#endif

		CF_MVVM.NotifyPropertyChanged(this);
	}

	string GetLayoutFile()
	{
		return string.Empty;
	}
};

typedef CF_ModuleGame CF_Module;
