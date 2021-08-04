class CF_Window : CF_Model
{
	private float m_PositionX;
	private float m_PositionY;

	private float m_Width;
	private float m_Height;

	private string m_Title;

	int m_Sort;

	private Widget title_bar_drag;
	private float m_DragOffsetX;
	private float m_DragOffsetY;
	private float m_ContentHeight;

	private Widget base_window;
	private Widget content;
 
	private ref CF_ModelBase m_Model;

	private CF_Window m_Above;
	private CF_Window m_Below;

	void CF_Window()
	{
		CF_MVVM.Create(this, GetLayoutFile(), CF_Windows._GetContainer());

		SetPosition(0, 0);
		SetSize(400, 400);

		if (CF_Windows.s_TopWindow)
		{
			CF_Windows.s_TopWindow.m_Above = this;
			m_Below = CF_Windows.s_TopWindow;
		}

		CF_Windows.s_TopWindow = this;
	}

	void ~CF_Window()
	{
		if (m_Above) m_Above.m_Below = m_Below;
		if (m_Below) m_Below.m_Above = m_Above;

		if (CF_Windows.s_TopWindow == this) CF_Windows.s_TopWindow = m_Below;

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
		return m_Below;
	}

	Widget GetWidgetRoot()
	{
		return base_window;
	}

	Widget CreateWidgets(string layoutFile)
	{
		Print(content);
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
		newContent.ClearFlags(WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE);
		newContent.SetPos(0, 0);
		newContent.SetSize(1, 1);
		return newContent;
	}

	Widget CreateWidgets(CF_ModelBase model, string layoutFile)
	{
		Print(content);
		Widget child = content.GetChildren();
		while (child != null)
		{
			Widget temp = child;
			child = child.GetSibling();
			temp.Unlink();
		}

		m_Model = model;

		Widget newContent = CF_MVVM.Create(m_Model, layoutFile, content).GetWidget();
		Print(newContent);
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

	void SetPosition(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetPosition", "" + x, "" + y);
		#endif
		
		m_PositionX = x;
		m_PositionY = y;

		NotifyPropertyChanged("m_PositionX");
		NotifyPropertyChanged("m_PositionY");
		
		if (title_bar_drag) title_bar_drag.SetPos(0, 0, true);
	}

	void SetSize(float x, float y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetSize", "" + x, "" + y);
		#endif
		
		m_Width = x;
		m_Height = y;
		m_ContentHeight = m_Height - 25;

		NotifyPropertyChanged("m_Width");
		NotifyPropertyChanged("m_Height");
		NotifyPropertyChanged("m_ContentHeight");
		
		if (title_bar_drag) title_bar_drag.SetPos(0, 0, true);
	}

	void OnCloseButtonClicked(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		#endif
		
		//delete this;
	}

	void OnMouseButtonDown(CF_ModelBase sender, CF_MouseEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseButtonDown", evt.ToStr());
		#endif

	}

	void OnDrag(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDrag", evt.ToStr());
		#endif
		
		m_DragOffsetX = evt.X - m_PositionX;
		m_DragOffsetY = evt.Y - m_PositionY;

		title_bar_drag.SetPos(0, 0, true);
		title_bar_drag.SetPos(0, 0, false);
	}

	void OnDragging(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDragging", evt.ToStr());
		#endif
		
		SetPosition(evt.X - m_DragOffsetX, evt.Y - m_DragOffsetY);
	}

	void OnDrop(CF_ModelBase sender, CF_DragEventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDrop", evt.ToStr());
		#endif
		
		SetPosition(evt.X - m_DragOffsetX, evt.Y - m_DragOffsetY);
	}
};
