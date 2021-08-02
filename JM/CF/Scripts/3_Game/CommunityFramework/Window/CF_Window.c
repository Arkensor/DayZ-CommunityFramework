class CF_Window : CF_Model
{
	private float m_PositionX;
	private float m_PositionY;

	private float m_Width;
	private float m_Height;

	private string m_Title;

	private int m_Sort;

	private Widget title_bar_drag;
	private float m_DragOffsetX;
	private float m_DragOffsetY;
	private float m_ContentHeight;
 
	private ref CF_ModelBase m_Model;

	private CF_WindowHandle m_Handle;

	void CF_Window(CF_WindowHandle handle)
	{
		m_Handle = handle;

		SetPosition(0, 0);
		SetSize(400, 400);
	}

	override string GetLayout()
	{
		return "JM/CF/GUI/layouts/windows/window.layout";
	}

	CF_WindowHandle GetHandle()
	{
		return m_Handle;
	}

	void SetTitle(string title)
	{
		CF_Trace trace(this, "SetTitle", "" + title);
		
		m_Title = title;

		NotifyPropertyChanged("m_Title");
	}

	void SetModel(CF_ModelBase model)
	{
		CF_Trace trace(this, "SetModel", "" + model);
		
		if (model != m_Model)
		{
			m_Model = model;

			NotifyPropertyChanged("m_Model");
		}
	}

	CF_ModelBase GetModel()
	{
		return m_Model;
	}

	void SetPosition(float x, float y)
	{
		CF_Trace trace(this, "SetPosition", "" + x, "" + y);
		
		m_PositionX = x;
		m_PositionY = y;

		NotifyPropertyChanged("m_PositionX");
		NotifyPropertyChanged("m_PositionY");
		
		if (title_bar_drag) title_bar_drag.SetPos(0, 0, true);
	}

	void SetSize(float x, float y)
	{
		CF_Trace trace(this, "SetSize", "" + x, "" + y);
		
		m_Width = x;
		m_Height = y;
		m_ContentHeight = m_Height - 25;

		NotifyPropertyChanged("m_Width");
		NotifyPropertyChanged("m_Height");
		NotifyPropertyChanged("m_ContentHeight");
		
		if (title_bar_drag) title_bar_drag.SetPos(0, 0, true);
	}

	void OnCloseButtonClicked(CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "OnCloseButtonClicked", evt.ToStr());
		
		CF_Windows.Destroy(m_Handle);
	}

	void OnMouseButtonDown(CF_MouseEventArgs evt)
	{
		CF_Trace trace(this, "OnMouseButtonDown", evt.ToStr());
		
		CF_Windows.Focus(m_Handle);
	}

	void OnDrag(CF_DragEventArgs evt)
	{
		CF_Trace trace(this, "OnDrag", evt.ToStr());
		
		m_DragOffsetX = evt.X - m_PositionX;
		m_DragOffsetY = evt.Y - m_PositionY;

		title_bar_drag.SetPos(0, 0, true);
		title_bar_drag.SetPos(0, 0, false);
	}

	void OnDragging(CF_DragEventArgs evt)
	{
		CF_Trace trace(this, "OnDragging", evt.ToStr());
		
		SetPosition(evt.X - m_DragOffsetX, evt.Y - m_DragOffsetY);
	}

	void OnDrop(CF_DragEventArgs evt)
	{
		CF_Trace trace(this, "OnDrop", evt.ToStr());
		
		SetPosition(evt.X - m_DragOffsetX, evt.Y - m_DragOffsetY);
	}

	void OnUpdate(CF_ViewEventArgs evt)
	{
		CF_Trace trace(this, "OnUpdate", evt.ToStr());
		
		int newSort = CF_Windows.ZIndex(m_Handle);
		if (m_Sort != newSort)
		{
			m_Sort = newSort;
			NotifyPropertyChanged("m_Sort");
		}
	}
};