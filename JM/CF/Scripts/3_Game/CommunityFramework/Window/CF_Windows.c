static autoptr CF_Windows g_CF_Windows;

class CF_Windows
{
	static CF_Window m_Head;
	static CF_Window m_Tail;

	private static Widget s_Container;

	private static bool m_FocusInput;
	private static bool m_WasFocusWindows;
	private static bool m_RespondingToMouse;

	private void CF_Windows()
	{
		CF_Timer.Create(this, "Update");
	}

	static void _Init()
	{
		if (g_CF_Windows) return;

		g_CF_Windows = new CF_Windows();
	}

	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "_Cleanup");
		#endif
		
		g_CF_Windows = null;
	}

	static void _MissionInit()
	{
		s_Container = GetGame().GetWorkspace().CreateWidgets("JM/CF/GUI/layouts/windows/container.layout", null);
	}

	static void _MissionCleanup()
	{
		s_Container.Unlink();
	}

	static Widget _GetContainer()
	{
		return s_Container;
	}

	static bool IsInputFocused()
	{
		return m_FocusInput;
	}

	static void InputFocus(bool shouldFocus)
	{
		m_FocusInput = shouldFocus;
	}

	void Update(CF_TimerBase timer, float dt)
	{
		CF_Window window = m_Tail;
		int numRemovesMouseFocus = 0;
		int index = 1;
		while (window != null)
		{
			window._SetSort(index++);

			if (window.DoesTakeGameFocus()) numRemovesMouseFocus++;

			window = window.GetPrev();
		}

		bool isMouseDown = (GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) != 0;

		if (m_RespondingToMouse && !isMouseDown)
		{
			m_RespondingToMouse = false;
		}
		else if (!m_RespondingToMouse && isMouseDown)
		{
			m_RespondingToMouse = true;

			if (!KeepMouseFocused() && IsInputFocused())
			{
				InputFocus(false);
			}
		}

		UpdateInputFocus();

		if (!m_RespondingToMouse) InputFocus(numRemovesMouseFocus > 0);
		
		s_Container.SetFlags(WidgetFlags.VEXACTSIZE | WidgetFlags.HEXACTSIZE);
		int w, h;
		GetScreenSize(w, h);
		s_Container.SetSize(w, h);
	}

	void UpdateInputFocus()
	{
		if (m_WasFocusWindows == m_FocusInput) return;

		m_WasFocusWindows = m_FocusInput;

		if (m_FocusInput)
		{
			GetGame().GetInput().ChangeGameFocus(1);
			
			SetFocus(NULL);
		}
		else
		{
			GetGame().GetInput().ChangeGameFocus(-1);
		}
		
		GetGame().GetUIManager().ShowUICursor(!GetGame().GetInput().HasGameFocus());
	}

	bool KeepMouseFocused()
	{
		if (CheckForFocus()) return true;

		Widget widget = GetWidgetUnderCursor();
		while (widget != null)
		{
			if (CheckWidgetForFocus(widget)) return true;

			widget = widget.GetParent();
		}

		return false;
	}

	bool CheckForFocus()
	{
		if (GetGame().GetUIManager().GetMenu()) return true;

		return false;
	}

	/*
	 * @note Function for modders to override
	 */
	bool CheckWidgetForFocus(Widget widget)
	{
		if (IsWidgetWindowRoot(widget)) return true;

		return false;
	}

	static bool IsWidgetWindowRoot(Widget widget)
	{  
		CF_Window window = m_Tail;
		while (window != null)
		{
			if (widget == window.GetWidgetRoot())
			{
				return true;
			}
			
			window = window.GetPrev();
		}

		return false;
	}
};
