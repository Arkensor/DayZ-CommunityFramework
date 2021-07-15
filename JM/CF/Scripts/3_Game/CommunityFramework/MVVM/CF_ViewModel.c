modded class CF_MVVM_View
{
	reference string Event_Click;
	reference string Event_ModalResult;
	reference string Event_DoubleClick;
	reference string Event_Select;
	reference string Event_ItemSelected;
	reference string Event_Focus;
	reference string Event_FocusLost;
	reference string Event_MouseEnter;
	reference string Event_MouseLeave;
	reference string Event_MouseWheel;
	reference string Event_MouseButtonDown;
	reference string Event_MouseButtonUp;
	reference string Event_Controller;
	reference string Event_KeyDown;
	reference string Event_KeyUp;
	reference string Event_KeyPress;
	reference string Event_Change;
	reference string Event_Drag;
	reference string Event_Dragging;
	reference string Event_DraggingOver;
	reference string Event_Drop;
	reference string Event_DropReceived;
	reference string Event_Resize;
	reference string Event_ChildAdd;
	reference string Event_ChildRemove;
	reference string Event_Update;
	reference string Event_Show;
	reference string Event_Hide;
	reference string Event_Destroyed;
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnClick", "" + w);

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (Event_Click != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Click, null, param);
		}

		return OnClick(evt);
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		CF_Trace trace(this, "OnModalResult", "" + w);

		CF_ModalEventArgs evt = new CF_ModalEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Code = code;
		evt.Result = result;

		if (Event_ModalResult != string.Empty)
		{
			Param param = new Param1<CF_ModalEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_ModalResult, null, param);
		}

		return OnModalResult(evt);
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnDoubleClick", "" + w);
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (Event_DoubleClick != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_DoubleClick, null, param);
		}

		return OnDoubleClick(evt);
	}
	
	override bool OnSelect(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnSelect", "" + w);

		CF_SelectEventArgs evt = new CF_SelectEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (Event_Select != string.Empty)
		{
			Param param = new Param1<CF_SelectEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Select, null, param);
		}

		return OnSelect(evt);
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		CF_Trace trace(this, "OnItemSelected", "" + w);

		CF_ItemSelectEventArgs evt = new CF_ItemSelectEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Row = row;
		evt.Column = column;
		evt.OldRow = oldRow;
		evt.OldColumn = oldColumn;

		if (Event_ItemSelected != string.Empty)
		{
			Param param = new Param1<CF_ItemSelectEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_ItemSelected, null, param);
		}

		return OnItemSelected(evt);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocus", "" + w);

		CF_PositionEventArgs evt = new CF_PositionEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (Event_Focus != string.Empty)
		{
			Param param = new Param1<CF_PositionEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Focus, null, param);
		}

		return OnFocus(evt);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocusLost", "" + w);
		
		CF_PositionEventArgs evt = new CF_PositionEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (Event_FocusLost != string.Empty)
		{
			Param param = new Param1<CF_PositionEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_FocusLost, null, param);
		}

		return OnFocusLost(evt);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnMouseEnter", "" + w);

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Type = 1;

		if (Event_MouseEnter != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_MouseEnter, null, param);
		}

		return OnMouseEnter(evt);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		CF_Trace trace(this, "OnMouseLeave", "" + w);

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Enter = enterW;
		evt.Type = 2;

		if (Event_MouseLeave != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_MouseLeave, null, param);
		}

		return OnMouseLeave(evt);
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		CF_Trace trace(this, "OnMouseWheel", "" + w);

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Wheel = wheel;

		if (Event_MouseWheel != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_MouseWheel, null, param);
		}

		return OnMouseWheel(evt);
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonDown", "" + w);
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (Event_MouseButtonDown != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonDown, null, param);
		}

		return OnMouseButtonDown(evt);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonUp", "" + w);
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (Event_MouseButtonUp != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonUp, null, param);
		}

		return OnMouseButtonUp(evt);
	}

	override bool OnController(Widget w, int control, int value)
	{
		CF_Trace trace(this, "OnController", "" + w);

		CF_ControllerEventArgs evt = new CF_ControllerEventArgs();
		evt.Target = w;
		evt.Control = control;
		evt.Value = value;

		if (Event_Controller == string.Empty)
		{
			Param param = new Param1<CF_ControllerEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Controller, null, param);
		}

		return OnController(evt);
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyDown", "" + w);
		
		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.DOWN;

		if (Event_KeyDown != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_KeyDown, null, param);
		}

		return OnKeyDown(evt);
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyUp", "" + w);

		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.UP;

		if (Event_KeyUp != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_KeyUp, null, param);
		}

		return OnKeyUp(evt);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyPress", "" + w);

		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.PRESS;

		if (Event_KeyPress != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_KeyPress, null, param);
		}

		return OnKeyPress(evt);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		CF_Trace trace(this, "OnChange", "" + w);
		
		CF_ChangeEventArgs evt = new CF_ChangeEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Finished = finished;

		if (Event_Change != string.Empty)
		{
			Param param = new Param1<CF_ChangeEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Change, null, param);
		}

		return OnChange(evt);
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnDrag", "" + w);
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = null;

		if (Event_Drag != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Drag, null, param);
		}

		return OnDrag(evt);
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDragging", "" + w);
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (Event_Dragging != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Dragging, null, param);
		}

		return OnDragging(evt);
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDraggingOver", "" + w);
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (Event_DraggingOver != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_DraggingOver, null, param);
		}

		return OnDraggingOver(evt);
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDrop", "" + w);

		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (Event_Drop != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Drop, null, param);
		}

		return OnDrop(evt);
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDropReceived", "" + w);

		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (Event_DropReceived != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_DropReceived, null, param);
		}

		return OnDropReceived(evt);
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnResize", "" + w);

		CF_ResizeEventArgs evt = new CF_ResizeEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (Event_Resize != string.Empty)
		{
			Param param = new Param1<CF_ResizeEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Resize, null, param);
		}

		return OnResize(evt);
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildAdd", "" + w);

		CF_ChildEventArgs evt = new CF_ChildEventArgs();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = false;

		if (Event_ChildAdd != string.Empty)
		{
			Param param = new Param1<CF_ChildEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_ChildAdd, null, param);
		}

		return OnChildAdd(evt);
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildRemove", "" + w);

		CF_ChildEventArgs evt = new CF_ChildEventArgs();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = true;

		if (Event_ChildRemove != string.Empty)
		{
			Param param = new Param1<CF_ChildEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_ChildRemove, null, param);
		}

		return OnChildRemove(evt);
	}
	
	override bool OnUpdate(Widget w)
	{
		CF_Trace trace(this, "OnUpdate", "" + w);

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (Event_Update != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Update, null, param);
		}

		return OnUpdate(evt);
	}
	
	bool OnShow(Widget w)
	{
		CF_Trace trace(this, "OnShow", "" + w);

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (Event_Show != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Show, null, param);
		}

		return true;
	}
	
	bool OnHide(Widget w)
	{
		CF_Trace trace(this, "OnHide", "" + w);

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (Event_Hide != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, Event_Hide, null, param);
		}

		return true;
	}
};