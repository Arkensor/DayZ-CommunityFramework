class CF_DebugUI : CF_DebugOutput
{
	private CF_Debug m_Parent;

	private string m_Data;
	private int m_TabDepth;

	private bool m_ViewInWorld;
	private Widget TextFieldLocked;

	private autoptr CF_Window m_Window;

	void CF_DebugUI(CF_Debug parent, string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_DebugUI");
#endif

		m_Parent = parent;

#ifndef COMPONENT_SYSTEM
		m_Window = new CF_Window(name);
		m_Window.SetTakesGameFocus(false);
		m_Window.CreateWidgets(this, GetLayoutFile());

		m_Window.OnClose.AddSubscriber(parent.Event_CloseWindow);
#endif

		ResetBuffer();

#ifdef COMPONENT_SYSTEM
		Add("Hello", "World");
		Add("Item", "Apple");
		Add("X", 5.1);
		Add("Y", 2);
		Add("Orientation", Vector(0, 5.0, 20.0));
		IncrementTab();
		Add("Items", "START");
		IncrementTab();
		Add("Item", "Orange");
		DecrementTab();
		Add("Items", "END");
		DecrementTab();
		PushBuffer();
#endif
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
		m_TabDepth = 0;
	}

	override void PushBuffer()
	{
		m_ViewInWorld = m_Parent.CanViewInWorld();

		CF_MVVM.NotifyPropertyChanged(this, "m_Data");
		CF_MVVM.NotifyPropertyChanged(this, "m_ViewInWorld");

#ifndef COMPONENT_SYSTEM
		if (m_ViewInWorld)
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
#endif
	}

	private string Tab()
	{
		string tab = "";
		for (int i = 0; i < m_TabDepth; i++)
		{
			tab += " ";
		}
		return tab;
	}

	private string NewLine()
	{
		if (m_Data == string.Empty)
			return Tab();

		return "\n" + Tab();
	}
};
