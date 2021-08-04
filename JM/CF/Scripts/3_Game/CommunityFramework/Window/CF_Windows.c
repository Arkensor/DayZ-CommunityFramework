static autoptr CF_Windows g_CF_Windows = null;

class CF_Windows
{
	static CF_Window s_TopWindow;

	private static Widget s_Container;

	private static bool m_FocusInput;
	private static bool m_WasFocusWindows;
	private static bool m_RespondingToMouse;

	private void CF_Windows()
	{
		CF_Timer.Create(this, "Update");
	}

	[CF_EventSubscriber(CF_Windows._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		if (g_CF_Windows) return;

		g_CF_Windows = new CF_Windows();
	}

	[CF_EventSubscriber(CF_Windows._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(g_CF_Windows, "_Cleanup");
		#endif
		
		g_CF_Windows = null;
	}

	[CF_EventSubscriber(CF_Windows._MissionInit, CF_LifecycleEvents.OnMissionCreate)]
	static void _MissionInit()
	{
		s_Container = GetGame().GetWorkspace().CreateWidgets( "JM/CF/GUI/layouts/windows/container.layout", NULL );
	}

	[CF_EventSubscriber(CF_Windows._MissionCleanup, CF_LifecycleEvents.OnMissionDestroy)]
	static void _MissionCleanup()
	{
		s_Container.Unlink();
	}

	static Widget _GetContainer()
	{
		return s_Container;
	}

	static bool IsWidgetWindowRoot(Widget widget)
	{  
		CF_Window window = s_TopWindow;
		while (window != null)
		{
			if (widget == window.GetWidgetRoot())
			{
				return true;
			}
			
			window = window.GetNext();
		}

		return false;
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
		CF_Window window = s_TopWindow;
		int index = 1;
		while (window != null)
		{
			window.m_Sort = index++;
			window.NotifyPropertyChanged("m_Sort");

			window = window.GetNext();
		}

		UpdateInputFocus();

		InputFocus(s_TopWindow != null);// && !m_RespondingToMouse);

		bool isMouseDown = (GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) != 0;

		if (m_RespondingToMouse && !isMouseDown)
		{
			m_RespondingToMouse = false;
		}
		else if (isMouseDown && IsInputFocused())
		{
			m_RespondingToMouse = true;

			if (!KeepMouseFocused())
			{
				InputFocus(false);
			}
		}
	}

	void UpdateInputFocus()
	{
		if (m_WasFocusWindows == m_FocusInput) return;

		m_WasFocusWindows = m_FocusInput;

		if (!m_FocusInput)
		{
			GetGame().GetInput().ChangeGameFocus(-1);
			GetGame().GetUIManager().ShowUICursor(false);
			
			SetFocus(NULL);
		}
		else
		{
			GetGame().GetInput().ChangeGameFocus(1);
			GetGame().GetUIManager().ShowUICursor(true);
		}
	}

	bool KeepMouseFocused()
	{
		if (!GetGame().GetUIManager().GetMenu()) return false;

		Widget widget = GetWidgetUnderCursor();
		while (widget != null)
		{
			if (IsWidgetWindowRoot(widget)) return true;

			if (CheckWidgetForFocus(widget)) return true;

			widget = widget.GetParent();
		}

		return false;
	}

	/*
	 * @note Function for modders to override
	 */
	bool CheckWidgetForFocus(Widget widget)
	{
		return false;
	}
};
