class CF_Popup : CF_Model
{
	// Ensures that only 1 root popup exists at a time
	private static autoptr CF_Popup s_Instance;

	ref CF_EventHandler OnDestroy = new CF_EventHandler();

	private bool m_WasMouseDown;

	private Widget popup_root;
	private float m_PositionX;
	private float m_PositionY;

	void CF_Popup()
	{
		s_Instance = this;
		
		CF_Timer.Create(this, "OnUpdate");
		CF_MVVM.Create(this, GetLayoutFile());
	}

	void ~CF_Popup()
	{
		OnDestroy.Invoke(this);
	}

	static bool IsOpen()
	{
		return s_Instance != null;
	}

	void OnUpdate(CF_TimerBase timer, float pDt)
	{
		bool isMouseDown = (GetMouseState(MouseState.LEFT) & MB_PRESSED_MASK) != 0;

		if (isMouseDown && m_WasMouseDown != isMouseDown)
		{
			bool closePopup = true;

			Widget widget = GetWidgetUnderCursor();
			while (widget != null)
			{
				if (widget == popup_root)
				{
					closePopup = false;
					break;
				}

				widget = widget.GetParent();
			}

			if (closePopup)
			{
				s_Instance = null;
				return;
			}
		}

		m_WasMouseDown = isMouseDown;
	}
};
