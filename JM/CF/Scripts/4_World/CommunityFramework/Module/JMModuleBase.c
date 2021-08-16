class CF_Module_Variable
{
	string m_Name;
	int m_Count; // max 4
	int m_AccessorIndices[4];
	typename m_AccessorTypes[4];
	CF_TypeConverter m_Converter;
};

class JMModuleBase
{
	protected bool m_Enabled;
	protected bool m_PreventInput;
	protected ref set< ref JMModuleBinding > m_Bindings;

	protected int m_NetSynchVariableCount;
	protected ref CF_Module_Variable[256] m_NetSynchVariables;
	
	void JMModuleBase()
	{
		m_Enabled = true;
		m_PreventInput = false;
		m_Bindings = new set< ref JMModuleBinding >;
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
	
	/**
	 * Only call in 'Init' and 'Constructor' on both client and server
	 */
	bool RegisterNetSyncVariable(string name)
	{
		// hard limit, no point attempting to sync more variables
		if (m_NetSynchVariableCount >= 256)
		{
			Error("ERROR: " + GetModuleName() + "::RegisterNetSyncVariable('" + name + "') -> More than 256 variables registered, got '" + m_NetSynchVariableCount + "'");
			return false;
		}

		CF_Module_Variable variable = new CF_Module_Variable();

		typename type = this.Type();
		array<string> tokens();
		name.Split(".", tokens);

		variable.m_Name = name;

		if (tokens.Count() != 0)
		{
			// Maximum of 3 tokens (max - 1)
			if (tokens.Count() >= 3)
			{
				Error("ERROR: " + GetModuleName() + "::RegisterNetSyncVariable('" + name + "') -> Variable depth more than 3, got '" + tokens.Count() + "'");
				return false;
			}

			variable.m_Name = tokens[tokens.Count() - 1];

			int i, j;

			// iterate over all tokens to get the sub class for the variable
			for (i = 0; i < tokens.Count() - 1; i++)
			{
				bool success = false;
				for (j = 0; j < type.GetVariableCount(); j++)
				{
					if (type.GetVariableName(j) == tokens[i])
					{
						type = type.GetVariableType(j);

						variable.m_AccessorIndices[variable.m_Count] = j;
						variable.m_AccessorTypes[variable.m_Count] = type;
						variable.m_Count++;

						success = true;

						break;
					}
				}

				// couldn't find sub variable
				if (!success)
				{
					Error("ERROR: " + GetModuleName() + "::RegisterNetSyncVariable('" + name + "') -> Couldn't find sub variable '" + tokens[i] + "'");
					return false;
				}
			}
		}

		for (j = 0; j < type.GetVariableCount(); j++)
		{
			if (type.GetVariableName(j) == variable.m_Name)
			{
				type = type.GetVariableType(j);

				variable.m_AccessorIndices[variable.m_Count] = j;
				variable.m_AccessorTypes[variable.m_Count] = type;
				variable.m_Count++;

				variable.m_Converter = CF_TypeConverters.Create(type);

				if (!variable.m_Converter)
				{
					Error("ERROR: " + GetModuleName() + "::RegisterNetSyncVariable('" + name + "') -> TypeConverter not found for type '" + type + "'");
					return false;
				}

				m_NetSynchVariables[m_NetSynchVariableCount] = variable;
				m_NetSynchVariableCount++;

				return true;
			}
		}

		Error("ERROR: " + GetModuleName() + "::RegisterNetSyncVariable('" + name + "') -> Couldn't find variable '" + variable.m_Name + "'");
		return false;
	}

	void SetSynchDirty()
	{
		ScriptRPC rpc = new ScriptRPC();

		rpc.Write(GetModuleName());

		CF_BinaryWriter writer = new CF_BinaryWriter(new CF_SerializerWriteStream(rpc));

		for (int i = 0; i < m_NetSynchVariableCount; i++)
		{
			CF_Module_Variable variable = m_NetSynchVariables[i];
			Class instance = this;

			int index = variable.m_Count - 1;
			
			for (int j = 0; j < index; j++)
			{
				if (!instance) break;
				
				variable.m_AccessorTypes[j].GetVariableValue(instance, variable.m_AccessorIndices[j], instance);
			}

			if (instance)
			{
				variable.m_Converter.FromTypename(instance, variable.m_AccessorIndices[index]);
			}

			variable.m_Converter.ToIO(writer);
		}

		writer.Close();

		rpc.Send(null, JMModuleManager.JM_VARIABLE_UPDATE, true, null);
	}

	void HandleNetSync(ParamsReadContext ctx)
	{
		CF_BinaryReader reader = new CF_BinaryReader(new CF_SerializerWriteStream(rpc));

		for (int i = 0; i < m_NetSynchVariableCount; i++)
		{
			CF_Module_Variable variable = m_NetSynchVariables[i];
			Class instance = this;

			int index = variable.m_Count - 1;
			
			for (int j = 0; j < index; j++)
			{
				if (!instance) break;

				variable.m_AccessorTypes[j].GetVariableValue(instance, variable.m_AccessorIndices[j], instance);
			}

			variable.m_Converter.FromIO(reader);

			if (instance)
			{
				variable.m_Converter.ToVariable(instance, variable.m_Name);
			}
		}

		reader.Close();

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
