class CF_DebugUI_Instance : CF_TimerBase
{
	private string m_Data = "";
	private int m_TabDepth = -1;

	private int m_DBGIndex;

	private autoptr CF_Window m_Window;
	private Class m_Class;

	void CF_DebugUI_Instance(Class cls, int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_DebugUI_Instance", "" + cls);
		#endif

		m_Class = cls;
		m_DBGIndex = index;
		
		m_Window = new CF_Window();
		m_Window.CreateWidgets(this, "JM/CF/GUI/layouts/debugui/debugui.layout");
	}

	void ~CF_DebugUI_Instance()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_DebugUI_Instance");
		#endif

		CF_DebugUI.s_Count--;
		CF_DebugUI.s_Instances[m_DBGIndex] = CF_DebugUI.s_Instances[CF_DebugUI.s_Count];
		CF_DebugUI.s_Instances[m_DBGIndex].m_DBGIndex = m_DBGIndex;
		CF_DebugUI.s_Instances[CF_DebugUI.s_Count] = null;
	}

	Class GetClass()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetClass");
		#endif

		return m_Class;
	}

	private string Tab()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Tab");
		#endif

		string tab = "";
		for (int i = 0; i < m_TabDepth; i++) tab += " ";
		return tab;
	}
	
	private string NewLine()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "NewLine");
		#endif

		return "\n" + Tab();
	}

	/**
	 * @brief Adds the value to the string. Formatted as "value"
	 */
	void Add(string value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + value);
		#endif

		m_Data += NewLine() + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, int value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + name, "" + value);
		#endif

		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, bool value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + name, "" + value);
		#endif

		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, float value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + name, "" + value);
		#endif

		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, string value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + name, "" + value);
		#endif

		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Calls the 'CF_DebugUI' method for the target Class, 'CF_DebugUI' must return true.
	 */
	void Add(Class value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Add", "" + value);
		#endif

		m_TabDepth++;

		if (!value)
		{
			Add("null");
			m_TabDepth--;
			return;
		}

		bool functionCallSuccess = false;
        GetGame().GameScript.CallFunctionParams(value, "CF_DebugUI", functionCallSuccess, new Param2<CF_DebugUI_Instance, CF_DebugUI_Type>(this, CF_DebugUI.s_Types));

		if (!functionCallSuccess)
		{
			Add("this", value.ClassName());

			typename type = value.Type();
			int count = type.GetVariableCount();
			for (int i = 0; i < count; i++)
			{
				string variableName = type.GetVariableName(i);
				typename variableType = type.GetVariableType(i);

				CF_TypeConverter converter = CF_TypeConverters.Create(variableType);
				if (converter.FromTypename(value, i))
				{
					Add(variableName, converter.GetString());
				}
			}
		}

		m_TabDepth--;
	}

	/**
	 * @brief Converts the 'Object' to a string, adds it to the string. Formatted as "name: object (network id)"
	 */
	void AddObject(string name, Object value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "AddObject", "" + name, "" + value);
		#endif

		string _value = "" + value;
		if (value) _value += "(" + value.GetNetworkIDString() + ")";
		Add(name, _value);
	}

	protected override void OnUpdate(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnUpdate", "" + dt);
		#endif

		m_Data = string.Empty;
		m_TabDepth = 0;

		Add(m_Class);

		CF_MVVM.NotifyPropertyChanged(this, "m_Data");
	}
};
