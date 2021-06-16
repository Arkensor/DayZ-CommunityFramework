class CF_ViewModel : ScriptedWidgetEventHandler
{
	private CF_MVVM_View m_View = null;
	private Class m_Model = null;
	private ref map<string, ref CF_MVVM_Property> m_Properties = new map<string, ref CF_MVVM_Property>();

	void CF_ViewModel(CF_MVVM_View view, Class model)
	{
		CF_Trace trace(this, "Create", "" + view, "" + model);

		SetView(view, false);
		SetModel(model);
	}

	void NotifyPropertyChanged(string name)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + name);
		
		CF_MVVM_Property property;
		if (!m_Properties.Find(name, property)) return;

		property.OnModel(m_Model);
	}

	void SetView(CF_MVVM_View view, bool loadProperties = true)
	{
		CF_Trace trace(this, "SetView", "" + view);

		if (m_View != view && m_View)
		{
			m_View.SetViewModel(null);
		}

		m_View = view;

		if (m_View)
		{
			m_View.SetViewModel(this);

			if (m_Model && loadProperties)
			{
				LoadProperties(m_View);
			}
		}
	}

	CF_MVVM_View GetView()
	{
		return m_View;
	}

	bool _DestroyView()
	{
		CF_Trace trace(this, "_DestroyView");

		Widget root = m_View.GetLayoutRoot();
		if (root)
		{
			root.Unlink();
			return true;
		}

		return false;
	}

	void SetModel(Class model)
	{
		CF_Trace trace(this, "SetModel", "" + model);

		m_Model = model;

		if (m_Model && m_View)
		{
			LoadProperties(m_View);
		}
	}

	Class GetModel()
	{
		return m_Model;
	}

	private void LoadProperties(CF_MVVM_View view)
	{
		CF_Trace trace(this, "LoadProperties", "" + view);
		
		view.GetProperties(m_Model, m_Properties);
		
		for (int i = 0; i < view.Count(); i++)
		{
			LoadProperties(view[i]);
		}
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnClick", "" + w);

		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Click == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Click, null, param);
		return !evt.Continue;
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		CF_Trace trace(this, "OnModalResult", "" + w);

		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_ModalResult == string.Empty) return false;

		CF_ModalEvent evt = new CF_ModalEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Code = code;
		evt.Result = result;

		Param param = new Param1<CF_ModalEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_ModalResult, null, param);
		return !evt.Continue;
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnDoubleClick", "" + w);

		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_DoubleClick == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_DoubleClick, null, param);
		return !evt.Continue;
	}
	
	override bool OnSelect(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnSelect", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Select == string.Empty) return false;

		CF_SelectEvent evt = new CF_SelectEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		Param param = new Param1<CF_SelectEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Select, null, param);
		return !evt.Continue;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		CF_Trace trace(this, "OnItemSelected", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_ItemSelected == string.Empty) return false;

		CF_ItemSelectEvent evt = new CF_ItemSelectEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Row = row;
		evt.Column = column;
		evt.OldRow = oldRow;
		evt.OldColumn = oldColumn;

		Param param = new Param1<CF_ItemSelectEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_ItemSelected, null, param);
		return !evt.Continue;
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocus", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Focus == string.Empty) return false;

		CF_PositionEvent evt = new CF_PositionEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		Param param = new Param1<CF_PositionEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Focus, null, param);
		return !evt.Continue;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocusLost", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_FocusLost == string.Empty) return false;

		CF_PositionEvent evt = new CF_PositionEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		Param param = new Param1<CF_PositionEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Click, null, param);
		return !evt.Continue;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnMouseEnter", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_MouseEnter == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_MouseEnter, null, param);
		return !evt.Continue;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		CF_Trace trace(this, "OnMouseLeave", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_MouseLeave == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Enter = enterW;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_MouseLeave, null, param);
		return !evt.Continue;
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		CF_Trace trace(this, "OnMouseWheel", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_MouseWheel == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Wheel = wheel;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_MouseWheel, null, param);
		return !evt.Continue;
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonDown", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_MouseButtonDown == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_MouseButtonDown, null, param);
		return !evt.Continue;
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonUp", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_MouseButtonUp == string.Empty) return false;

		CF_MouseEvent evt = new CF_MouseEvent();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		Param param = new Param1<CF_MouseEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_MouseButtonUp, null, param);
		return !evt.Continue;
	}

	override bool OnController(Widget w, int control, int value)
	{
		CF_Trace trace(this, "OnController", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Controller == string.Empty) return false;

		CF_ControllerEvent evt = new CF_ControllerEvent();
		evt.Target = w;
		evt.Control = control;
		evt.Value = value;

		Param param = new Param1<CF_ControllerEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Controller, null, param);
		return !evt.Continue;
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyDown", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_KeyDown == string.Empty) return false;

		CF_KeyEvent evt = new CF_KeyEvent();
		evt.Target = w;
		evt.Key = key;
		evt.State = CF_KeyState.DOWN;

		Param param = new Param1<CF_KeyEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_KeyDown, null, param);
		return !evt.Continue;
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyUp", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_KeyUp == string.Empty) return false;

		CF_KeyEvent evt = new CF_KeyEvent();
		evt.Target = w;
		evt.Key = key;
		evt.State = CF_KeyState.UP;

		Param param = new Param1<CF_KeyEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_KeyUp, null, param);
		return !evt.Continue;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyPress", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_KeyPress == string.Empty) return false;

		CF_KeyEvent evt = new CF_KeyEvent();
		evt.Target = w;
		evt.Key = key;
		evt.State = CF_KeyState.PRESS;

		Param param = new Param1<CF_KeyEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_KeyPress, null, param);
		return !evt.Continue;
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		CF_Trace trace(this, "OnChange", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Change == string.Empty) return false;

		CF_ChangeEvent evt = new CF_ChangeEvent();
		evt.Target = w;
		evt.Finished = finished;

		Param param = new Param1<CF_ChangeEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Change, null, param);
		return !evt.Continue;
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnDrag", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Drag == string.Empty) return false;

		CF_DragEvent evt = new CF_DragEvent();
		evt.Target = w;
		evt.Reciever = null;

		Param param = new Param1<CF_DragEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Drag, null, param);
		return !evt.Continue;
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDragging", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Dragging == string.Empty) return false;

		CF_DragEvent evt = new CF_DragEvent();
		evt.Target = w;
		evt.Reciever = reciever;

		Param param = new Param1<CF_DragEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Dragging, null, param);
		return !evt.Continue;
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDraggingOver", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_DraggingOver == string.Empty) return false;

		CF_DragEvent evt = new CF_DragEvent();
		evt.Target = w;
		evt.Reciever = reciever;

		Param param = new Param1<CF_DragEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_DraggingOver, null, param);
		return !evt.Continue;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDrop", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Drop == string.Empty) return false;

		CF_DragEvent evt = new CF_DragEvent();
		evt.Target = w;
		evt.Reciever = reciever;

		Param param = new Param1<CF_DragEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Drop, null, param);
		return !evt.Continue;
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDropReceived", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_DropReceived == string.Empty) return false;

		CF_DragEvent evt = new CF_DragEvent();
		evt.Target = w;
		evt.Reciever = reciever;

		Param param = new Param1<CF_DragEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_DropReceived, null, param);
		return !evt.Continue;
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnResize", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Resize == string.Empty) return false;

		CF_ResizeEvent evt = new CF_ResizeEvent();
		evt.Target = w;

		Param param = new Param1<CF_ResizeEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Resize, null, param);
		return !evt.Continue;
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildAdd", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_ChildAdd == string.Empty) return false;

		CF_ChildEvent evt = new CF_ChildEvent();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = false;

		Param param = new Param1<CF_ChildEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_ChildAdd, null, param);
		return !evt.Continue;
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildRemove", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_ChildRemove == string.Empty) return false;

		CF_ChildEvent evt = new CF_ChildEvent();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = true;

		Param param = new Param1<CF_ChildEvent>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_ChildRemove, null, param);
		return !evt.Continue;
	}
	
	override bool OnUpdate(Widget w)
	{
		CF_Trace trace(this, "OnUpdate", "" + w);
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding) return false;
		if (binding.Event_Update == string.Empty) return false;

		CF_Event evt = new CF_Event();
		evt.Target = w;

		Param param = new Param1<CF_Event>(evt);
		g_Script.CallFunctionParams(m_Model, binding.Event_Update, null, param);
		return !evt.Continue;
	}
};