class CF_Window : CF_Model
{
	autoptr CF_EventHandler OnClose = new CF_EventHandler();

	autoptr CF_EventHandler OnFocus = new CF_EventHandler();
	autoptr CF_EventHandler OnUnfocus = new CF_EventHandler();

	// Attached
	private CF_ModelBase m_Model;

	// Sorting
	private CF_Window m_Prev;
	private CF_Window m_Next;
	private int m_Sort;

	// Widgets
	private Widget base_window;
	private Widget content;

	// Properties
	private bool m_Visible;

	private float m_PositionX;
	private float m_PositionY;

	private float m_Width;
	private float m_Height;
	private float m_MinimumWidth;
	private float m_MinimumHeight;
	private float m_MaximumWidth;
	private float m_MaximumHeight;

	private int m_BorderColor;
	private int m_BorderHoverColor;
	private int m_BorderDragColor;

	private string m_Title;

	private bool m_TakesGameFocus;

	// State
	private bool m_FullScreen;
	private bool m_Minimized;

	private bool m_IsFocused;
	private bool m_WasFocused;

	private float m_ContentWidth;
	private float m_ContentHeight;

	private float m_PreviousPositionX;
	private float m_PreviousPositionY;
	private float m_PreviousWidth;
	private float m_PreviousHeight;

	// Dragging/Resizing
	private float m_DragOffsetX;
	private float m_DragOffsetY;
	private float m_ResizeStartX;
	private float m_ResizeStartY;

	private int m_BorderUColor;
	private int m_BorderDColor;
	private int m_BorderLColor;
	private int m_BorderRColor;
	private int m_BorderULColor;
	private int m_BorderURColor;
	private int m_BorderDLColor;
	private int m_BorderDRColor;

	void CF_Window(string title = "Window", int width = 400, int height = 400)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3(this, "CF_Window").Add(title).Add(width).Add(height);
		#endif

		m_Visible = true;

		m_MinimumWidth = 100;
		m_MinimumHeight = 25;

		m_MaximumWidth = 10000;
		m_MaximumHeight = 10000;

		m_BorderColor = ARGB(0, 0, 0, 0);
		m_BorderHoverColor = ARGB(150, 255, 0, 255);
		m_BorderDragColor = ARGB(255, 255, 0, 255);

		m_TakesGameFocus = true;

		Add();

		CF_MVVM.Create(this, GetLayoutFile(), CF_Windows._GetContainer());

		SetTitle(title);
		SetPosition(0, 0);
		SetSize(width, height);
	}

	void ~CF_Window()
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_Window");
		#endif

		OnClose.Invoke(this);

		Remove();

		if (m_Model)
		{
			CF_MVVM.Destroy(m_Model);
		}
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/windows/window.layout";
	}

	CF_Window GetNext()
	{
		return m_Next;
	}

	CF_Window GetPrev()
	{
		return m_Prev;
	}

	Widget GetWidgetRoot()
	{
		return base_window;
	}

	Widget CreateWidgets(string layoutFile)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "CreateWidgets").Add(layoutFile);
		#endif

		Widget child = content.GetChildren();
		while (child != null)
		{
			Widget temp = child;
			child = child.GetSibling();
			temp.Unlink();
		}
		
		WorkspaceWidget wSpace = GetGame().GetWorkspace();
		// A mess to fix an issue in Workbench, can also substitute for loading screen support
		if (wSpace == null)
		{
			wSpace = GetGame().GetLoadingWorkspace();
			if (!wSpace) wSpace = CF.Game().GetWorkspace();
			if (!wSpace) wSpace = CF.Game().GetLoadingWorkspace();

			if (!wSpace) return null;
		}

		Widget newContent = wSpace.CreateWidgets(layoutFile, content);
		if (!newContent) return null;
		
		newContent.ClearFlags(WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE);
		newContent.SetPos(0, 0);
		newContent.SetSize(1, 1);
		return newContent;
	}

	Widget CreateWidgets(CF_ModelBase model, string layoutFile)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "CreateWidgets").Add(model).Add(layoutFile);
		#endif

		Widget child = content.GetChildren();
		while (child != null)
		{
			Widget temp = child;
			child = child.GetSibling();
			temp.Unlink();
		}

		m_Model = model;

		Widget newContent = CF_MVVM.Create(m_Model, layoutFile, content).GetWidget();
		if (!newContent) return null;

		newContent.ClearFlags(WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE);
		newContent.SetPos(0, 0);
		newContent.SetSize(1, 1);
		return newContent;
	}

	void SetTitle(string title)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetTitle").Add(title);
		#endif
		
		m_Title = title;

		NotifyPropertyChanged("m_Title");
	}

	string GetTitle()
	{
		return m_Title;
	}

	void SetVisible(bool visible)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetVisible").Add(visible);
		#endif
		
		m_Visible = visible;

		NotifyPropertyChanged("m_Visible");
	}

	bool IsVisible()
	{
		return m_Visible;
	}

	void SetTakesGameFocus(bool takes)
	{
		m_TakesGameFocus = takes;
	}

	bool DoesTakeGameFocus()
	{
		return m_TakesGameFocus;
	}

	void SetModel(CF_ModelBase model)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetModel").Add(model);
		#endif
		
		if (model != m_Model)
		{
			m_Model = model;

			//NotifyPropertyChanged("m_Model");
		}
	}

	CF_ModelBase GetModel()
	{
		return m_Model;
	}

	void SetFullscreen(bool fullscreen, bool wasDrag = false)
	{
		if (m_FullScreen == fullscreen) return;

		m_FullScreen = fullscreen;
		NotifyPropertyChanged("m_FullScreen");

		if (m_FullScreen)
		{
			m_PreviousWidth = m_Width;
			m_PreviousHeight = m_Height;

			m_PreviousPositionX = m_PositionX;
			m_PreviousPositionY = m_PositionY;
			
			int w, h;
			GetScreenSize(w, h);

			SetSize(w, h);
			SetPosition(0, 0);
		}
		else
		{
			SetSize(m_PreviousWidth, m_PreviousHeight);
			if (!wasDrag) SetPosition(m_PreviousPositionX, m_PreviousPositionY);
		}
	}

	void SetMinimized(bool minimized)
	{
		m_Minimized = minimized;
		NotifyPropertyChanged("m_Minimized");
	}

	void UpdateFocus(bool focused)
	{
		m_IsFocused = focused;
		if (m_IsFocused == m_WasFocused) return;
		m_WasFocused = m_IsFocused;

		if (m_IsFocused)
		{
			OnFocus.Invoke(this, null);
		}
		else
		{
			SetFocus(null);

			OnUnfocus.Invoke(this, null);
		}
	}

	void SetPosition(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetPosition").Add(x).Add(y);
		#endif
		
		m_PositionX = x;
		m_PositionY = y;

		NotifyPropertyChanged("m_PositionX");
		NotifyPropertyChanged("m_PositionY");
	}

	void SetSize(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetSize").Add(x).Add(y);
		#endif
		
		m_Width = x;
		m_Height = y + 29;

		if (m_Width < m_MinimumWidth) m_Width = m_MinimumWidth;
		else if (m_Width > m_MaximumWidth) m_Width = m_MaximumWidth;
		if (m_Height < m_MinimumHeight) m_Height = m_MinimumHeight;
		else if (m_Height > m_MaximumHeight) m_Height = m_MaximumHeight;

		m_ContentWidth = m_Width;
		m_ContentHeight = m_Height - 29;

		NotifyPropertyChanged("m_Width");
		NotifyPropertyChanged("m_Height");
		NotifyPropertyChanged("m_ContentWidth");
		NotifyPropertyChanged("m_ContentHeight");
	}

	void OnMinimizeButtonClicked(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnCloseButtonClicked").Add(args.GetDebugName());
		#endif

		SetMinimized(true);
	}

	void OnExpandButtonClicked(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnCloseButtonClicked").Add(args.GetDebugName());
		#endif

		SetMinimized(false);
	}

	void OnWindowButtonClicked(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnCloseButtonClicked").Add(args.GetDebugName());
		#endif

		SetFullscreen(false);
	}

	void OnFullscreenButtonClicked(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnCloseButtonClicked").Add(args.GetDebugName());
		#endif

		SetFullscreen(true);
	}

	void OnCloseButtonClicked(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnCloseButtonClicked").Add(args.GetDebugName());
		#endif
		
		delete this;
	}

	void OnMouseButtonDown(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnMouseButtonDown").Add(args.GetDebugName());
		#endif

		BringTop();
	}

	void OnDrag(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnDrag").Add(args.GetDebugName());
		#endif
		
		if (m_FullScreen)
		{
			float newX = args.X - (m_PreviousWidth * 0.5);
			if (newX < 0) newX = 0;
			else if (newX > m_Width) newX = m_Width - m_PreviousWidth;

			SetPosition(newX, 0.0);
		}
		
		m_DragOffsetX = args.X - m_PositionX;
		m_DragOffsetY = args.Y - m_PositionY;
		
		SetFullscreen(false, true);
	}

	void OnDragging(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnDragging").Add(args.GetDebugName());
		#endif
		
		SetPosition(args.X - m_DragOffsetX, args.Y - m_DragOffsetY);
	}

	void OnStartResizing(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnStartResizing").Add(args.GetDebugName());
		#endif

		m_ResizeStartX = args.X;
		m_ResizeStartY = args.Y;

		m_PreviousWidth = m_Width;
		m_PreviousHeight = m_Height;

		m_PreviousPositionX = m_PositionX;
		m_PreviousPositionY = m_PositionY;
	}

	void OnStopResizing(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnStartResizing").Add(args.GetDebugName());
		#endif

		SetFocus(null);
	}

	void OnResizingUp(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeY = m_PreviousHeight - (args.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (args.Y - m_ResizeStartY);
		if (newPosY + m_MinimumHeight > m_PreviousPositionY + m_PreviousHeight) newPosY = m_PreviousPositionY + m_PreviousHeight;
		SetSize(m_PreviousWidth, newSizeY - 29);
		SetPosition(m_PreviousPositionX, newPosY);

		ResetBorder();
		m_BorderUColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderUColor");
	}

	void OnResizingDown(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeY = m_PreviousHeight + (args.Y - m_ResizeStartY);
		SetSize(m_PreviousWidth, newSizeY - 29);

		ResetBorder();
		m_BorderDColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderDColor");
	}

	void OnResizingLeft(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth - (args.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (args.X - m_ResizeStartX);
		SetSize(newSizeX, m_PreviousHeight - 29);
		SetPosition(newPosX, m_PreviousPositionY);

		ResetBorder();
		m_BorderLColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderLColor");
	}

	void OnResizingRight(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth + (args.X - m_ResizeStartX);
		SetSize(newSizeX, m_PreviousHeight - 29);

		ResetBorder();
		m_BorderRColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderRColor");
	}

	void OnResizingUpLeft(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth - (args.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (args.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight - (args.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (args.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY - 29);
		SetPosition(newPosX, newPosY);

		ResetBorder();
		m_BorderULColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderULColor");
	}

	void OnResizingUpRight(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth + (args.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight - (args.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (args.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY - 29);
		SetPosition(m_PreviousPositionX, newPosY);

		ResetBorder();
		m_BorderURColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderURColor");
	}

	void OnResizingDownLeft(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth - (args.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (args.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight + (args.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY - 29);
		SetPosition(newPosX, m_PreviousPositionY);

		ResetBorder();
		m_BorderDLColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderDLColor");
	}

	void OnResizingDownRight(CF_ModelBase sender, CF_DragEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnResizingUp").Add(args.GetDebugName());
		#endif

		float newSizeX = m_PreviousWidth + (args.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight + (args.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY - 29);

		ResetBorder();
		m_BorderDRColor = m_BorderDragColor;
		NotifyPropertyChanged("m_BorderDRColor");
	}

	void OnMouseBorderUp(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderUColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderUColor");
		}
	}

	void OnMouseBorderDown(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderDColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderDColor");
		}
	}

	void OnMouseBorderLeft(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderLColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderLColor");
		}
	}

	void OnMouseBorderRight(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderRColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderRColor");
		}
	}

	void OnMouseBorderUpLeft(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderULColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderULColor");
		}
	}

	void OnMouseBorderUpRight(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderURColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderURColor");
		}
	}

	void OnMouseBorderDownLeft(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderDLColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderDLColor");
		}
	}

	void OnMouseBorderDownRight(CF_ModelBase sender, CF_MouseEventArgs args)
	{
		ResetBorder();

		if (args.Type == 1)
		{
			m_BorderDRColor = m_BorderHoverColor;
			NotifyPropertyChanged("m_BorderDRColor");
		}
	}

	void ResetBorder()
	{
		m_BorderUColor = m_BorderColor;
		m_BorderDColor = m_BorderColor;
		m_BorderLColor = m_BorderColor;
		m_BorderRColor = m_BorderColor;
		m_BorderULColor = m_BorderColor;
		m_BorderURColor = m_BorderColor;
		m_BorderDLColor = m_BorderColor;
		m_BorderDRColor = m_BorderColor;

		NotifyPropertyChanged("m_BorderUColor");
		NotifyPropertyChanged("m_BorderDColor");
		NotifyPropertyChanged("m_BorderLColor");
		NotifyPropertyChanged("m_BorderRColor");
		NotifyPropertyChanged("m_BorderULColor");
		NotifyPropertyChanged("m_BorderURColor");
		NotifyPropertyChanged("m_BorderDLColor");
		NotifyPropertyChanged("m_BorderDRColor");
	}

	/*private*/ void _SetSort(int sort)
	{
		m_Sort = sort;
		NotifyPropertyChanged("m_Sort");
	}

	private CF_Window Add()
	{
		CF_Window _this = this;

		if (!CF_Windows.s_Head)
		{
			CF_Windows.s_Head = _this;
			CF_Windows.s_Tail = _this;
		}
		else
		{
			m_Next = CF_Windows.s_Head;
			CF_Windows.s_Head.m_Prev = _this;
			CF_Windows.s_Head = _this;
		}

		return _this;
	}

	private CF_Window Insert(CF_Window previous)
	{
		CF_Window _this = this;

		if (!previous)
		{
			m_Prev = null;
			m_Next = CF_Windows.s_Head;
			CF_Windows.s_Head.m_Prev = _this;
			CF_Windows.s_Head = _this;
		}
		else if (!previous.m_Next)
		{
			m_Next = null;
			m_Prev = CF_Windows.s_Tail;
			CF_Windows.s_Tail.m_Next = _this;
			CF_Windows.s_Tail = _this;
		}
		else
		{
			m_Prev = previous;
			m_Next = m_Prev.m_Next;
			m_Next.m_Prev = this;
			m_Prev.m_Next = this;
		}

		return _this;
	}

	private CF_Window Remove()
	{
		CF_Window _this = this;

		if (m_Next)
		{
			m_Next.m_Prev = m_Prev;
		}
		else
		{
			CF_Windows.s_Tail = m_Prev;
		}

		if (m_Prev)
		{
			m_Prev.m_Next = m_Next;
		}
		else
		{
			CF_Windows.s_Head = m_Next;
		}

		m_Prev = null;
		m_Next = null;

		return _this;
	}

	void BringUp()
	{
		CF_Window _this = this;

		CF_Window prev = null;
		if (m_Prev) prev = m_Prev.m_Prev;

		if (m_Prev || m_Next)
		{
			// Incrementing the reference count, so this window doesn't get destroyed.
			_this = Remove();
		} else return;

		Insert(prev);

		return;
	}

	void BringDown()
	{
		CF_Window _this = this;

		CF_Window prev = m_Next;

		if (m_Prev || m_Next)
		{
			// Incrementing the reference count, so this window doesn't get destroyed.
			_this = Remove();
		} else return;

		Insert(prev);

		return;
	}

	void BringTop()
	{
		CF_Window _this = this;

		if (CF_Windows.s_Head == _this) return;

		if (m_Prev || m_Next)
		{
			// Incrementing the reference count, so this window doesn't get destroyed.
			_this = Remove();
		} else return;

		Add();
	}
};