class CF_DebugUI_Instance : CF_TimerBase
{
	private string m_Data = "";
	private int m_TabDepth = -1;

	private string m_Title;
	private autoptr CF_Window m_Window;
	private Class m_Class;

	void CF_DebugUI_Instance(Class cls, string title)
	{
		m_Class = cls;
		m_Title = title;

		SetInterval(0);
	}

	protected override void OnStart()
	{
		if (m_Window) return;
		
		m_Window = new CF_Window(m_Title);
		m_Window.SetTakesGameFocus(false);
		m_Window.CreateWidgets(this, "JM/CF/GUI/layouts/debugui/debugui.layout");
	}

	protected override void OnStop()
	{
		m_Window = null;
	}

	Class GetClass()
	{
		return m_Class;
	}

	private string Tab()
	{
		string tab = "";
		for (int i = 0; i < m_TabDepth; i++) tab += " ";
		return tab;
	}
	
	private string NewLine()
	{
		return "\n" + Tab();
	}

	/**
	 * @brief Adds the value to the string. Formatted as "value"
	 */
	void Add(string value)
	{
		m_Data += NewLine() + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, int value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, bool value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, float value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, vector value)
	{
		m_Data += NewLine() + name + ": " + value[0] + ", " + value[1] + ", " + value[2];
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	void Add(string name, string value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Calls the 'CF_DebugUI' method for the target Class, 'CF_DebugUI' must return true.
	 */
	void Add(Class value)
	{
		m_TabDepth++;

		if (!value)
		{
			Add("null");
			m_TabDepth--;
			return;
		}

		bool functionCallSuccess = false;
        GetGame().GameScript.CallFunctionParams(value, "CF_OnDebugUpdate", functionCallSuccess, new Param2<CF_DebugUI_Instance, CF_DebugUI_Type>(this, CF_DebugUI.s_Types));

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

	void Add(string name, Class value)
	{
		Object obj;
		if (Class.CastTo(obj, value))
		{
			AddObject(name, obj);
			return;
		}

		string clsVal = "null";
		if (value) clsVal = "" + value;
		Add(name, clsVal);
	}

	/**
	 * @brief Converts the 'Object' to a string, adds it to the string. Formatted as "name: object (network id)"
	 */
	void AddObject(string name, Object value)
	{
		string _value = "" + value;
		if (value) _value += "(" + value.GetNetworkIDString() + ")";
		Add(name, _value);
	}

	protected override void OnTick(float dt)
	{
		m_Data = string.Empty;
		m_TabDepth = 0;

		Add(m_Class);

		CF_MVVM.NotifyPropertyChanged(this, "m_Data");
	}
};
