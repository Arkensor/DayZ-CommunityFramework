static autoptr CF_Windows g_CF_Windows;

enum CF_WindowsFocusState
{
	WORLD = 0,
	WINDOW
};

enum CF_WindowsInputState
{
	RELEASE = 0,
	PRESS
};

class CF_Windows
{
	static CF_Window s_Head;
	static CF_Window s_Tail;

	static int s_Count;

	private static Widget s_Container;

	private static UAInput s_ToggleInput;
	private static CF_WindowsFocusState s_PreservedState;

	private static CF_WindowsFocusState s_State;
	private static CF_WindowsFocusState s_PreviousState;

	private static bool s_Override;
	private static CF_WindowsFocusState s_OverrideState;

	private static CF_WindowsInputState s_InputState;
	private static CF_WindowsInputState s_PreviousInputState;
	private static bool s_InputForcingLossOfFocus;

	private void CF_Windows()
	{
		#ifndef NO_GUI
		CF_Timer.Create(this, "Update");
		#endif
	}

	static void _Init()
	{
		if (g_CF_Windows) return;

		g_CF_Windows = new CF_Windows();
	}

	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(g_CF_Windows, "_Cleanup");
		#endif
		
		g_CF_Windows = null;
	}

	static void _MissionInit()
	{
		Print("_MissionInit");

		#ifdef SERVER
		return;
		#endif

		s_ToggleInput = GetUApi().GetInputByName("UACFToggleWindowMode");

		if (s_Container)
			return;

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

	static bool IsWidgetWindowRoot(Widget widget)
	{  
		CF_Window window = s_Tail;
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

	static UAInput GetInput()
	{
		return s_ToggleInput;
	}

	static void SetState(CF_WindowsFocusState state)
	{
		s_PreservedState = state;
	}

	static CF_WindowsFocusState GetState()
	{
		return s_PreservedState;
	}

	static void FlipState()
	{
		if (s_PreservedState == CF_WindowsFocusState.WORLD)
		{
			s_PreservedState = CF_WindowsFocusState.WINDOW;
			return;
		}

		s_PreservedState = CF_WindowsFocusState.WORLD;
	}

	static void OverrideInputState(bool pOverride, CF_WindowsFocusState pState = CF_WindowsFocusState.WORLD)
	{
		s_Override = pOverride;
		s_OverrideState = pState;
	}

	void Update(CF_TimerBase timer, float dt)
	{
		#ifdef SERVER
		timer.Stop();
		return;
		#endif

		if (!s_Container)
		{
			if (GetDayZGame() && !GetDayZGame().IsLoading())
			{
				_MissionInit();
			}
			
			return;
		}

		s_Count = 0;

		CF_Window window = s_Tail;
		while (window != null)
		{
			if (window.GetPrev())
			{
				window.UpdateFocus(false);
			}

			window._SetSort(s_Count++);
			window = window.GetPrev();
		}

		if (s_ToggleInput && s_ToggleInput.LocalPress()) // Flip the state when the key is pressed
		{
			FlipState();
		}

		if (s_InputForcingLossOfFocus) // Left mouse button pressed in the world
		{
			s_State = CF_WindowsFocusState.WORLD;
		}
		else if (s_Override) // Some mod overriding the input
		{
			s_State = s_OverrideState;
		}
		else if (s_Count <= 0 || CheckForFocus()) // No windows avaliable
		{
			s_State = CF_WindowsFocusState.WORLD;
			s_PreservedState = s_State;
		}
		else // Default behaviour
		{
			s_State = s_PreservedState;
		}

		// Update the state change
		if (s_State != s_PreviousState)
		{
			s_PreviousState = s_State;

			OnStateChanged();
		}

		if (window)
		{
			window.UpdateFocus(s_State == CF_WindowsFocusState.WORLD);
		}

		// Delay input state change by 1 frame
		if (s_PreviousInputState != s_InputState)
		{
			s_PreviousInputState = s_InputState;

			OnInputStateChanged();
		}

		bool isMouseDown = (GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) != 0;
		switch (s_InputState)
		{
			case CF_WindowsInputState.PRESS:
				if (!isMouseDown) s_InputState = CF_WindowsInputState.RELEASE;
				break;
			case CF_WindowsInputState.RELEASE:
				if (isMouseDown) s_InputState = CF_WindowsInputState.PRESS;
				break;
		}
		
		s_Container.SetFlags(WidgetFlags.VEXACTSIZE | WidgetFlags.HEXACTSIZE);
		int w, h;
		GetScreenSize(w, h);
		s_Container.SetSize(w, h);
	}

	void OnInputStateChanged()
	{
		s_InputForcingLossOfFocus = false;

		if (s_InputState == CF_WindowsInputState.PRESS)
		{
			if (!KeepMouseFocused())
			{
				s_InputForcingLossOfFocus = true;
			}
		}
	}

	void OnStateChanged()
	{
		if (s_State == CF_WindowsFocusState.WINDOW)
		{
			GetGame().GetInput().ChangeGameFocus(1);
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

		if (CF_Popup.IsOpen()) return true;

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
};
