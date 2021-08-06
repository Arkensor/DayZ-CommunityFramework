class CF_Window : CF_Model
{
	private float m_PositionX;
	private float m_PositionY;

	private float m_Width;
	private float m_Height;

	private bool m_FullScreen;
	private bool m_Minimized;

	private float m_PreviousWidth;
	private float m_PreviousHeight;

	private float m_PreviousPositionX;
	private float m_PreviousPositionY;

	private string m_Title;

	private int m_Sort;

	private Widget title_bar_drag;
	private float m_DragOffsetX;
	private float m_DragOffsetY;
	private float m_ContentHeight;

	private float m_ResizeStartX;
	private float m_ResizeStartY;
	private Widget border_up;
	private Widget border_down;
	private Widget border_left;
	private Widget border_right;
	private Widget border_upleft;
	private Widget border_upright;
	private Widget border_downleft;
	private Widget border_downright;

	private Widget base_window;
	private Widget content;
 
	private ref CF_ModelBase m_Model;

	private CF_Window m_Prev;
	private CF_Window m_Next;

	private bool m_TakesGameFocus;

	void CF_Window(string title = "Window", int width = 400, int height = 400)
	{
		m_TakesGameFocus = true;

		SetTitle(title);
		SetPosition(0, 0);
		SetSize(width, height);

		CF_MVVM.Create(this, GetLayoutFile(), CF_Windows._GetContainer());

		Add();
	}

	void ~CF_Window()
	{
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
		CF_Trace trace(this, "SetTitle", "" + title);
		#endif
		
		m_Title = title;

		NotifyPropertyChanged("m_Title");
	}

	string GetTitle()
	{
		return m_Title;
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
		CF_Trace trace(this, "SetModel", "" + model);
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

			SetSize(w - 300, h);
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

	void SetPosition(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetPosition", "" + x, "" + y);
		#endif
		
		m_PositionX = x;
		m_PositionY = y;

		NotifyPropertyChanged("m_PositionX");
		NotifyPropertyChanged("m_PositionY");

		FixDraggables();
	}

	void SetSize(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetSize", "" + x, "" + y);
		#endif
		
		m_Width = x;
		m_Height = y;

		if (m_Width < 100) m_Width = 100;
		if (m_Height < 25) m_Height = 25;

		m_ContentHeight = m_Height - 25;

		NotifyPropertyChanged("m_Width");
		NotifyPropertyChanged("m_Height");
		NotifyPropertyChanged("m_ContentHeight");

		FixDraggables();
	}

	void OnMinimizeButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif

		SetMinimized(true);
	}

	void OnExpandButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif

		SetMinimized(false);
	}

	void OnWindowButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif

		SetFullscreen(false);
	}

	void OnFullscreenButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif

		SetFullscreen(true);
	}

	void OnCloseButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif
		
		delete this;
	}

	void OnMouseButtonDown(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseButtonDown", evt.ToStr());
		#endif

		BringTop();
	}

	void OnDrag(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDrag", evt.ToStr());
		#endif
		
		if (m_FullScreen)
		{
			float newX = evt.X - (m_PreviousWidth * 0.5);
			if (newX < 0) newX = 0;
			else if (newX > m_Width) newX = m_Width - m_PreviousWidth;

			SetPosition(newX, 0.0);
		}
		
		m_DragOffsetX = evt.X - m_PositionX;
		m_DragOffsetY = evt.Y - m_PositionY;
		
		SetFullscreen(false, true);
	}

	void OnDragging(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDragging", evt.ToStr());
		#endif
		
		SetPosition(evt.X - m_DragOffsetX, evt.Y - m_DragOffsetY);
	}

	void OnStartResizing(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnStartResizing", evt.ToStr());
		#endif

		m_ResizeStartX = evt.X;
		m_ResizeStartY = evt.Y;

		m_PreviousWidth = m_Width;
		m_PreviousHeight = m_Height;

		m_PreviousPositionX = m_PositionX;
		m_PreviousPositionY = m_PositionY;

		FixDraggables();
	}

	void OnStopResizing(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnStartResizing", evt.ToStr());
		#endif

		SetFocus(null);

		FixDraggables();
	}

	void OnResizingUp(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeY = m_PreviousHeight - (evt.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (evt.Y - m_ResizeStartY);
		SetSize(m_PreviousWidth, newSizeY);
		SetPosition(m_PreviousPositionX, newPosY);

		FixDraggables();
	}

	void OnResizingDown(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeY = m_PreviousHeight + (evt.Y - m_ResizeStartY);
		SetSize(m_PreviousWidth, newSizeY);

		FixDraggables();
	}

	void OnResizingLeft(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth - (evt.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (evt.X - m_ResizeStartX);
		SetSize(newSizeX, m_PreviousHeight);
		SetPosition(newPosX, m_PreviousPositionY);

		FixDraggables();
	}

	void OnResizingRight(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth + (evt.X - m_ResizeStartX);
		SetSize(newSizeX, m_PreviousHeight);

		FixDraggables();
	}

	void OnResizingUpLeft(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth - (evt.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (evt.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight - (evt.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (evt.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY);
		SetPosition(newPosX, newPosY);

		FixDraggables();
	}

	void OnResizingUpRight(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth + (evt.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight - (evt.Y - m_ResizeStartY);
		float newPosY = m_PreviousPositionY + (evt.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY);
		SetPosition(m_PreviousPositionX, newPosY);

		FixDraggables();
	}

	void OnResizingDownLeft(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth - (evt.X - m_ResizeStartX);
		float newPosX = m_PreviousPositionX + (evt.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight + (evt.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY);
		SetPosition(newPosX, m_PreviousPositionY);

		FixDraggables();
	}

	void OnResizingDownRight(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResizingUp", evt.ToStr());
		#endif

		float newSizeX = m_PreviousWidth + (evt.X - m_ResizeStartX);
		float newSizeY = m_PreviousHeight + (evt.Y - m_ResizeStartY);

		SetSize(newSizeX, newSizeY);

		FixDraggables();
	}

	void FixDraggables()
	{
		title_bar_drag.SetPos(0, 0, true);
		title_bar_drag.SetPos(0, 0, false);

		border_up.SetPos(0, 0, true);
		border_down.SetPos(0, 0, true);
		border_left.SetPos(0, 0, true);
		border_right.SetPos(0, 0, true);

		border_up.SetPos(0, 0, false);
		border_down.SetPos(0, 0, false);
		border_left.SetPos(0, 0, false);
		border_right.SetPos(0, 0, false);
	}

	/*private*/ void _SetSort(int sort)
	{
		m_Sort = sort;
		NotifyPropertyChanged("m_Sort");
	}

	private CF_Window Add()
	{
		CF_Window _this = this;

		if (!CF_Windows.m_Head)
		{
			CF_Windows.m_Head = _this;
			CF_Windows.m_Tail = _this;
		}
		else
		{
			m_Next = CF_Windows.m_Head;
			CF_Windows.m_Head.m_Prev = _this;
			CF_Windows.m_Head = _this;
		}

		return _this;
	}

	private CF_Window Insert(CF_Window previous)
	{
		CF_Window _this = this;

		if (!previous)
		{
			m_Prev = null;
			m_Next = CF_Windows.m_Head;
			CF_Windows.m_Head.m_Prev = _this;
			CF_Windows.m_Head = _this;
		}
		else if (!previous.m_Next)
		{
			m_Next = null;
			m_Prev = CF_Windows.m_Tail;
			CF_Windows.m_Tail.m_Next = _this;
			CF_Windows.m_Tail = _this;
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
			CF_Windows.m_Tail = m_Prev;
		}

		if (m_Prev)
		{
			m_Prev.m_Next = m_Next;
		}
		else
		{
			CF_Windows.m_Head = m_Next;
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

		if (CF_Windows.m_Head == _this) return;

		if (m_Prev || m_Next)
		{
			// Incrementing the reference count, so this window doesn't get destroyed.
			_this = Remove();
		} else return;

		Add();
	}
};
