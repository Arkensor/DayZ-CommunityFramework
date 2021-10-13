class CF_DebugUI : CF_DebugOutput
{
	private CF_Debug m_Parent;

	private string m_Data;
	private int m_TabDepth;

	private bool m_LockPosition;
	private Widget TextFieldLocked;

	private autoptr CF_Window m_Window;

	void CF_DebugUI(CF_Debug parent, string name)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_DebugUI");
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
		auto trace = CF_Trace_0(this, "~CF_DebugUI");
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
		
		m_LockPosition = true;
		CF_MVVM.NotifyPropertyChanged(this, "m_LockPosition");

		if (m_LockPosition)
		{
			vector position = m_Parent.GetPosition();

			Object obj;
			if (Class.CastTo(obj, m_Parent.GetInstance()))
			{
				position = obj.ModelToWorld(position);
			}

			position = GetGame().GetScreenPos(position);
			if (position[2] <= 0.0)
			{
				m_Window.SetVisible(false);
			}
			else
			{
				m_Window.SetVisible(true);
			}

			m_Window.SetPosition(position[0], position[1]);

			float sizeX, sizeY;
			TextFieldLocked.GetScreenSize(sizeX, sizeY);

			m_Window.SetSize(sizeX, sizeY);
		}
	}

	private string Tab()
	{
		string tab = "";
		for (int i = 0; i < m_TabDepth; i++) tab += " ";
		return tab;
	}
	
	private string NewLine()
	{
		if (m_Data == string.Empty)
			return Tab();
			
		return "\n" + Tab();
	}
};
