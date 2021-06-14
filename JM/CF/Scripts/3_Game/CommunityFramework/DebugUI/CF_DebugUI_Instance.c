class CF_DebugUI_Instance
{
	private string m_Data = "";
	private int m_TabDepth = -1;

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
	void Add(string name, string value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Calls the 'CF_DebugUI' method for the target Class
	 */
	void Add(Class value)
	{
		m_TabDepth++;
        GetGame().GameScript.CallFunctionParams(value, "CF_DebugUI", null, new Param2<CF_DebugUI_Instance, CF_DebugUI_Type>(this, CF.DebugUI.Types));
		m_TabDepth--;
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
};