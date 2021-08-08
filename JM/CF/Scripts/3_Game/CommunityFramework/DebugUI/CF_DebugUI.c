class CF_DebugUI : CF_DebugOutput
{
	private CF_Debug m_Parent;

	private string m_Data;
	private int m_TabDepth;

	private autoptr CF_Window m_Window;

	void CF_DebugUI(CF_Debug parent, string name)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_DebugUI");
		#endif

		m_Parent = parent;

		m_Window = new CF_Window(name);
		m_Window.SetTakesGameFocus(false);
		m_Window.CreateWidgets(this, GetLayoutFile());

		m_Window.OnClose.AddSubscriber(parent.Event_CloseWindow);

		ResetBuffer();
	}

	void ~CF_DebugUI()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_DebugUI");
		#endif
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/debug/debugui.layout";
	}

	override void SetName(string name)
	{
		m_Window.SetTitle(name);
	}

	/**
	 * @brief Adds the value to the string. Formatted as "value"
	 */
	override void Add(string value)
	{
		m_Data += NewLine() + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	override void Add(string name, int value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	override void Add(string name, bool value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	override void Add(string name, float value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	override void Add(string name, vector value)
	{
		m_Data += NewLine() + name + ": " + value[0] + ", " + value[1] + ", " + value[2];
	}

	/**
	 * @brief Adds the name and value to the string. Formatted as "name: value"
	 */
	override void Add(string name, string value)
	{
		m_Data += NewLine() + name + ": " + value;
	}

	override void IncrementTab()
	{
		m_TabDepth++;
	}

	override void DecrementTab()
	{
		m_TabDepth--;
	}

	override void ResetBuffer()
	{
		m_Data = string.Empty;
		m_TabDepth = -1;
	}

	override void PushBuffer()
	{
		CF_MVVM.NotifyPropertyChanged(this, "m_Data");
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
};
