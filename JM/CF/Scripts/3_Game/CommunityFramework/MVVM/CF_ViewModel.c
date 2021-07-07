class CF_ViewModel : ScriptedWidgetEventHandler
{
	private CF_MVVM_View m_View = null;
	private CF_ModelBase m_Model = null;

	private ref array<ref CF_MVVM_Property> m_Properties = new array<ref CF_MVVM_Property>();
	private ref map<string, ref CF_MVVM_Property> m_PropertiesMap = new map<string, ref CF_MVVM_Property>();

	void CF_ViewModel(CF_MVVM_View view, CF_ModelBase model)
	{
		CF_Trace trace(this, "CF_ViewModel", "" + view, "" + model);

		SetView(view, false);
		SetModel(model);
	}

	void ~CF_ViewModel()
	{
		CF_Trace trace(this, "~CF_ViewModel");
	}

	void NotifyPropertyChanged(string name, CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, "" + temp.String());
		
		CF_MVVM_Property property;
		if (!m_PropertiesMap.Find(name, property)) return;

		property.OnModel(m_Model, temp);
	}

	void NotifyPropertyChanged(CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + temp.String());

		for (int i = 0; i < m_Properties.Count(); i++)
		{
			m_Properties[i].OnModel(m_Model, temp);
		}
	}

	void NotifyViewPropertyChanged(string name, CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, "" + temp.String());
		
		CF_MVVM_Property property;
		if (!m_PropertiesMap.Find(name, property)) return;

		property.OnView(m_Model, temp);
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

	void _UnlinkView()
	{
		CF_Trace trace(this, "_UnlinkView");

		if (m_View)
		{
			m_View.SetViewModel(null);

			Widget root = m_View.GetWidget();
			if (root)
			{
				root.Unlink();
			}
		}
	}

	bool _DestroyView()
	{
		CF_Trace trace(this, "_DestroyView");

		if (m_View)
		{
			Widget root = m_View.GetWidget();
			if (root)
			{
				root.Unlink();

				return true;
			}
		}

		return false;
	}

	void SetModel(CF_ModelBase model)
	{
		CF_Trace trace(this, "SetModel", "" + model);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif

		m_Model = model;

		if (m_Model && m_View)
		{
			LoadProperties(m_View);

			CF.MVVM._LoadPropertyTypes(m_Model, m_View, m_PropertiesMap, m_Properties);

			NotifyPropertyChanged();
		}
	}

	CF_ModelBase GetModel()
	{
		return m_Model;
	}

	private void LoadProperties(CF_MVVM_View view)
	{
		CF_Trace trace(this, "LoadProperties", "" + view);
		
		view.GetProperties(this, m_PropertiesMap, m_Properties);

		set<CF_MVVM_View> children = view.GetChildren();
		for (int i = 0; i < children.Count(); i++)
		{
			LoadProperties(children[i]);
		}
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnClick", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (binding.Event_Click != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Click, null, param);
		}

		return binding.OnClick(evt);
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		CF_Trace trace(this, "OnModalResult", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif

		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ModalEventArgs evt = new CF_ModalEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Code = code;
		evt.Result = result;

		if (binding.Event_ModalResult != string.Empty)
		{
			Param param = new Param1<CF_ModalEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_ModalResult, null, param);
		}

		return binding.OnModalResult(evt);
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnDoubleClick", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif

		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (binding.Event_DoubleClick != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_DoubleClick, null, param);
		}

		return binding.OnDoubleClick(evt);
	}
	
	override bool OnSelect(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnSelect", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_SelectEventArgs evt = new CF_SelectEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (binding.Event_Select != string.Empty)
		{
			Param param = new Param1<CF_SelectEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Select, null, param);
		}

		return binding.OnSelect(evt);
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		CF_Trace trace(this, "OnItemSelected", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ItemSelectEventArgs evt = new CF_ItemSelectEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Row = row;
		evt.Column = column;
		evt.OldRow = oldRow;
		evt.OldColumn = oldColumn;

		if (binding.Event_ItemSelected != string.Empty)
		{
			Param param = new Param1<CF_ItemSelectEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_ItemSelected, null, param);
		}

		return binding.OnItemSelected(evt);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocus", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_PositionEventArgs evt = new CF_PositionEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (binding.Event_Focus != string.Empty)
		{
			Param param = new Param1<CF_PositionEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Focus, null, param);
		}

		return binding.OnFocus(evt);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocusLost", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_PositionEventArgs evt = new CF_PositionEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (binding.Event_FocusLost != string.Empty)
		{
			Param param = new Param1<CF_PositionEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_FocusLost, null, param);
		}

		return binding.OnFocusLost(evt);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnMouseEnter", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Type = 1;

		if (binding.Event_MouseEnter != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_MouseEnter, null, param);
		}

		return binding.OnMouseEnter(evt);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		CF_Trace trace(this, "OnMouseLeave", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Enter = enterW;
		evt.Type = 2;

		if (binding.Event_MouseLeave != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_MouseLeave, null, param);
		}

		return binding.OnMouseLeave(evt);
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		CF_Trace trace(this, "OnMouseWheel", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = -1;
		evt.Wheel = wheel;

		if (binding.Event_MouseWheel != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_MouseWheel, null, param);
		}

		return binding.OnMouseWheel(evt);
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonDown", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (binding.Event_MouseButtonDown != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_MouseButtonDown, null, param);
		}

		return binding.OnMouseButtonDown(evt);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonUp", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_MouseEventArgs evt = new CF_MouseEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Button = button;

		if (binding.Event_MouseButtonUp != string.Empty)
		{
			Param param = new Param1<CF_MouseEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_MouseButtonUp, null, param);
		}

		return binding.OnMouseButtonUp(evt);
	}

	override bool OnController(Widget w, int control, int value)
	{
		CF_Trace trace(this, "OnController", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ControllerEventArgs evt = new CF_ControllerEventArgs();
		evt.Target = w;
		evt.Control = control;
		evt.Value = value;

		if (binding.Event_Controller == string.Empty)
		{
			Param param = new Param1<CF_ControllerEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Controller, null, param);
		}

		return binding.OnController(evt);
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyDown", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.DOWN;

		if (binding.Event_KeyDown != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_KeyDown, null, param);
		}

		return binding.OnKeyDown(evt);
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyUp", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.UP;

		if (binding.Event_KeyUp != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_KeyUp, null, param);
		}

		return binding.OnKeyUp(evt);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyPress", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_KeyEventArgs evt = new CF_KeyEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Key = key;
		evt.State = CF_KeyState.PRESS;

		if (binding.Event_KeyPress != string.Empty)
		{
			Param param = new Param1<CF_KeyEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_KeyPress, null, param);
		}

		return binding.OnKeyPress(evt);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		CF_Trace trace(this, "OnChange", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_ChangeEventArgs evt = new CF_ChangeEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Finished = finished;

		if (binding.Event_Change != string.Empty)
		{
			Param param = new Param1<CF_ChangeEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Change, null, param);
		}

		return binding.OnChange(evt);
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnDrag", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = null;

		if (binding.Event_Drag != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Drag, null, param);
		}

		return binding.OnDrag(evt);
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDragging", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (binding.Event_Dragging != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Dragging, null, param);
		}

		return binding.OnDragging(evt);
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDraggingOver", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;
		
		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (binding.Event_DraggingOver != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_DraggingOver, null, param);
		}

		return binding.OnDraggingOver(evt);
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDrop", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (binding.Event_Drop != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Drop, null, param);
		}

		return binding.OnDrop(evt);
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDropReceived", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_DragEventArgs evt = new CF_DragEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;
		evt.Reciever = reciever;

		if (binding.Event_DropReceived != string.Empty)
		{
			Param param = new Param1<CF_DragEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_DropReceived, null, param);
		}

		return binding.OnDropReceived(evt);
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnResize", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ResizeEventArgs evt = new CF_ResizeEventArgs();
		evt.Target = w;
		evt.X = x;
		evt.Y = y;

		if (binding.Event_Resize != string.Empty)
		{
			Param param = new Param1<CF_ResizeEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Resize, null, param);
		}

		return binding.OnResize(evt);
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildAdd", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ChildEventArgs evt = new CF_ChildEventArgs();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = false;

		if (binding.Event_ChildAdd != string.Empty)
		{
			Param param = new Param1<CF_ChildEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_ChildAdd, null, param);
		}

		return binding.OnChildAdd(evt);
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildRemove", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ChildEventArgs evt = new CF_ChildEventArgs();
		evt.Target = w;
		evt.Child = child;
		evt.Remove = true;

		if (binding.Event_ChildRemove != string.Empty)
		{
			Param param = new Param1<CF_ChildEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_ChildRemove, null, param);
		}

		return binding.OnChildRemove(evt);
	}
	
	override bool OnUpdate(Widget w)
	{
		CF_Trace trace(this, "OnUpdate", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (binding.Event_Update != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Update, null, param);
		}

		return binding.OnUpdate(evt);
	}
	
	bool OnShow(Widget w)
	{
		CF_Trace trace(this, "OnShow", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (binding.Event_Show != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Show, null, param);
		}

		return true;
	}
	
	bool OnHide(Widget w)
	{
		CF_Trace trace(this, "OnHide", "" + w);

		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
		CF.MVVM._Assign(this);
		#endif

		if (!w) return false;
		
		CF_Widget binding;
		w.GetScript(binding);
		if (!binding || !binding.IsBinded(this)) return false;

		CF_ViewEventArgs evt = new CF_ViewEventArgs();
		evt.Target = w;

		if (binding.Event_Hide != string.Empty)
		{
			Param param = new Param1<CF_ViewEventArgs>(evt);
			g_Script.CallFunctionParams(m_Model, binding.Event_Hide, null, param);
		}

		return true;
	}
};