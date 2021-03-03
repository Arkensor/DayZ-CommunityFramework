enum CF_Module_VariableType
{
	INT, FLOAT, BOOL
};

class CF_Module_Variable
{
	string Name;
	autoptr array<int> AccessorIndices();
	autoptr array<typename> AccessorTypes();
	CF_Module_VariableType Type;
};

class JMModuleBase
{
	protected bool m_Enabled;
	protected bool m_PreventInput;
	protected ref set< ref JMModuleBinding > m_Bindings;
	protected ref array<CF_Module_Variable> m_NetSynchVariables;
	
	void JMModuleBase()
	{
		m_Enabled = true;
		m_PreventInput = false;
		m_Bindings = new set< ref JMModuleBinding >;
		m_NetSynchVariables = new array<CF_Module_Variable>();
	}
	
	void ~JMModuleBase()
	{
	}
	
	void Init()
	{
		RegisterKeyMouseBindings();
	}

	void Toggle()
	{
		m_Enabled = !m_Enabled;
	}

	void PreventInput(bool prevent)
	{
		m_PreventInput = prevent;
	}

	string GetModuleName()
	{
		return ClassName();
	}

	typename GetModuleType()
	{
		return GetModuleName().ToType();
	}

	bool IsEnabled()
	{
		return m_Enabled;
	}

	bool IsPreventingInput()
	{
		return m_PreventInput;
	}

	/**
	 * Can't change dynamically, only used on module init, if false 
	 * and is mission host, the module is destroyed and forgotten.
	 */
	bool IsServer()
	{
		return true;
	}

	/**
	 * Can't change dynamically, only used on module init, if false 
	 * and is mission client, the module is destroyed and forgotten.
	 */
	bool IsClient()
	{
		return true;
	}

	void RegisterKeyMouseBindings() 
	{
	}
	
	bool RegisterNetSyncVariable(string name)
	{
		// hard limit, max 1kb for synching.
		if (m_NetSynchVariables.Count() > 256) return false;

		CF_Module_Variable variable = new CF_Module_Variable();

		typename cls = this.Type();
		array<string> tokens();
		name.Split(".", tokens);

		// don't know how split works, this might not be needed
		if (tokens.Count() == 0) tokens.Insert(name);

		// iterate over all tokens to get the sub class for the variable
		for (int i = 0; i < tokens.Count() - 1; i++)
		{
			bool success = false;
			for (int j = 0; j < cls.GetVariableCount(); j++)
			{
				if (cls.GetVariableName(j) == tokens[i])
				{
					variable.AccessorIndices.Insert(j);
					variable.AccessorTypes.Insert(cls);

					cls = cls.GetVariableType(j);

					success = true;

					break; // break bad
				}
			}

			// couldn't find sub variable
			if (!success) return false;
		}

		variable.Name = tokens[tokens.Count() - 1];

		for (int k = 0; k < cls.GetVariableCount(); k++)
		{
			if (cls.GetVariableName(k) == variable.Name)
			{
				variable.AccessorIndices.Insert(k);
				variable.AccessorTypes.Insert(cls);

				cls = cls.GetVariableType(k);

				if (type == int)
				{
					variable.Type = CF_Module_VariableType.INT;
					m_NetSynchVariables.Insert(variable);
					return true;
				}

				if (type == float)
				{
					variable.Type = CF_Module_VariableType.FLOAT;
					m_NetSynchVariables.Insert(variable);
					return true;
				}

				if (type == bool)
				{
					variable.Type = CF_Module_VariableType.BOOL;
					m_NetSynchVariables.Insert(variable);
					return true;
				}

				break;
			}
		}

		return false;
	}

	void SetSynchDirty()
	{
		ScriptRPC rpc = new ScriptRPC();

		for (int i = 0; i < m_NetSynchVariables.Count(); i++)
		{
			CF_Module_Variable variable = m_NetSynchVariables[i];
			Class cls = this;
			
			for (int j = 0; j < variable.AccessorIndices.Count() - 1; j++)
			{
				variable.AccessorTypes[j].GetVariableValue(cls, variable.AccessorIndices[j], cls);
			}

			int idx = variable.AccessorIndices.Count() - 1;

			switch (variable.Type)
			{
				case CF_Module_VariableType.BOOL:
					bool val_Bool;
					variable.AccessorTypes[idx].GetVariableValue(cls, variable.AccessorIndices[idx], val_Bool);
					rpc.Write(val_Bool);
					break;
				case CF_Module_VariableType.INT:
					int val_Int;
					variable.AccessorTypes[idx].GetVariableValue(cls, variable.AccessorIndices[idx], val_Int);
					rpc.Write(val_Int);
					break;
				case CF_Module_VariableType.FLOAT:
					float val_Float;
					variable.AccessorTypes[idx].GetVariableValue(cls, variable.AccessorIndices[idx], val_Float);
					rpc.Write(val_Float);
					break;
			}
		}

		rpc.Send(null, JMModuleManager.JM_VARIABLE_UPDATE, true, null);
	}

	void HandleNetSync(ref ParamsReadContext ctx)
	{
		for (int i = 0; i < m_NetSynchVariables.Count(); i++)
		{
			CF_Module_Variable variable = m_NetSynchVariables[i];
			Class cls = this;
			
			for (int j = 0; j < variable.AccessorIndices.Count() - 1; j++)
			{
				variable.AccessorTypes[j].GetVariableValue(cls, variable.AccessorIndices[j], cls);
			}

			switch (variable.Type)
			{
				case CF_Module_VariableType.BOOL:
					bool val_Bool;
					rpc.Read(val_Bool)
					EnScript.SetClassVar(cls, variable.Name, 0, val_Bool);
					break;
				case CF_Module_VariableType.INT:
					int val_Int;
					rpc.Read(val_Int)
					EnScript.SetClassVar(cls, variable.Name, 0, val_Int);
					break;
				case CF_Module_VariableType.FLOAT:
					float val_Float;
					rpc.Read(val_Float)
					EnScript.SetClassVar(cls, variable.Name, 0, val_Float);
					break;
			}
		}

		OnVariablesSynchronized();
	}
	
	/**
	 * Deprecated, use RegisterBinding instead.
	 */
	void RegisterKeyMouseBinding( JMModuleBinding binding ) 
	{
		RegisterBinding( binding );
		Error( GetModuleName() + "::RegisterKeyMouseBinding has been deprecated, use " + GetModuleName() + "::RegisterBinding instead." );
	}

	void RegisterBinding( JMModuleBinding binding ) 
	{
		m_Bindings.Insert( binding );
	}
	
	set< ref JMModuleBinding > GetBindings()
	{
		return m_Bindings;
	}

	// Events 

	/**
	 * Is called every mission frame
	 * 
	 * @timeslice time of previous update
	 */
	void OnUpdate( float timeslice ) 
	{
	}

	void OnSettingsUpdated()
	{
	}

	void OnClientPermissionsUpdated()
	{
	}

	void OnInit()
	{
	}
	
	void OnMissionStart()
	{
	}
	
	void OnMissionFinish()
	{
	}
	
	void OnMissionLoaded()
	{
	}

	void OnVariablesSynchronized()
	{
	}

	void OnRPC( PlayerIdentity sender, Object target, int rpc_type, ref ParamsReadContext ctx )
	{
	}

	int GetRPCMin()
	{
		return -1;
	}

	int GetRPCMax()
	{
		return -1;
	}

	/**
	 * @brief See: WorldCleaupEventTypeID
	 */
	void OnWorldCleanup()
	{
	}

	/**
	 * @brief See: MPSessionStartEventTypeID
	 */
	void OnMPSessionStart()
	{
	}

	/**
	 * @brief See: MPSessionPlayerReadyEventTypeID
	 */
	void OnMPSessionPlayerReady()
	{
	}

	/**
	 * @brief See: MPSessionFailEventTypeID
	 */
	void OnMPSessionFail()
	{
	}

	/**
	 * @brief See: MPSessionEndEventTypeID
	 */
	void OnMPSessionEnd()
	{
	}

	/**
	 * @brief See: ConnectingAbortEventTypeID
	 */
	void OnMPConnectAbort()
	{
	}

	/**
	 * @brief See: MPConnectionLostEventTypeID
	 */
	void OnMPConnectionLost( int duration )
	{
	}

	/**
	 * @brief See: RespawnEventTypeID
	 */
	void OnRespawn( int time )
	{
	}

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled( PlayerBase player, PlayerIdentity identity )
	{
	}

	/**
	 * @brief See: MissionServer::InvokeOnConnect
	 */
	void OnInvokeConnect( PlayerBase player, PlayerIdentity identity )
	{
	}

	/**
	 * @brief See: MissionServer::InvokeOnDisconnect
	 */
	void OnInvokeDisconnect( PlayerBase player )
	{
	}

	/**
	 * @brief See: ClientNewEventTypeID
	 */
	void OnClientNew( out PlayerBase player, PlayerIdentity identity, vector pos, ParamsReadContext ctx )
	{
	}

	/**
	 * @brief See: ClientRespawnEventTypeID
	 */
	void OnClientRespawn( PlayerBase player, PlayerIdentity identity )
	{
	}

	/**
	 * @brief See: ClientReadyEventTypeID
	 */
	void OnClientReady( PlayerBase player, PlayerIdentity identity )
	{
	}

	/**
	 * @brief See: ClientPrepareEventTypeID
	 */
	void OnClientPrepare( PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout )
	{
	}

	/**
	 * @brief See: ClientReconnectEventTypeID
	 */
	void OnClientReconnect( PlayerBase player, PlayerIdentity identity )
	{
	}

	/**
	 * @brief See: ClientDisconnectedEventTypeID
	 */
	void OnClientLogout( PlayerBase player, PlayerIdentity identity, int logoutTime, bool authFailed )
	{
	}

	/**
	 * @brief See: MissionServer::PlayerDisconnected - Fires when the player has disconnected from the server (OnClientReconnect won't fire)
	 */
	void OnClientDisconnect( PlayerBase player, PlayerIdentity identity, string uid )
	{
	}

	/**
	 * @brief See: LogoutCancelEventTypeID
	 */
	void OnClientLogoutCancelled( PlayerBase player )
	{
	}
}
