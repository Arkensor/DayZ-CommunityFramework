class CF_ViewModel : ScriptedWidgetEventHandler
{
	reference string Model;
	reference string Children;

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

	protected Widget m_Widget;

    #ifdef COMPONENT_SYSTEM 
	private ref CF_ModelBase m_WB_Model;
	#endif

	//! In-game, the ref count shouldn't be incremented. When the ref count == 0, then this view should be destroyed.
	protected CF_ModelBase m_Model;

	//! Lifetimes are managed by the enfusion widgets
	protected CF_ViewModel m_Parent = null;
	protected ref set<CF_ViewModel> m_Children = new set<CF_ViewModel>();

	protected ref CF_Map<string, ref CF_MVVM_Property> m_Properties = new CF_Map<string, ref CF_MVVM_Property>();

	protected CF_Map<string, ref CF_MVVM_Property> m_TempProperties;
	
	void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		m_Widget = w;

		if (Model != string.Empty)
		{
			typename modelType = Model.ToType();
			if (modelType)
			{
				//! Workbench editing
    			#ifdef COMPONENT_SYSTEM
				if (!CF_MVVM.WB_NEXT_IN_SCRIPT)
				{
					Class.CastTo(m_WB_Model, modelType.Spawn());
					m_Model = m_WB_Model;
					SetModel(m_Model);
				}
				#endif
			}
			else
			{
				Model = "";
			}
		}

		if (Model == string.Empty)
		{
			Widget parent = w.GetParent();
			while (parent != null)
			{
				CF_ViewModel view = null;
				parent.GetScript(view);
				if (view)
				{
					SetParent(view);
					break;
				}

				parent = parent.GetParent();
			}
		}
	}

	void ~CF_ViewModel()
	{
		CF_Trace trace(this, "~CF_ViewModel");
	}

	void NotifyPropertyChanged(string name, CF_EventArgs args = null)
	{
		CF_EventArgs temp = args;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, "" + temp);

		if (name == string.Empty) return;

		CF_MVVM_Property property;
		if (!m_Properties.Find(name, property)) return;

		property.OnView(temp);
	}

	void NotifyPropertyChanged(CF_EventArgs args = null)
	{
		CF_EventArgs temp = args;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + temp.ToStr());

		for (int i = 0; i < m_Properties.Count(); i++)
		{
			CF_MVVM_Property property = m_Properties.GetElement(i);
			property.OnView(temp);
		}
	}

	void SetModel(CF_ModelBase model)
	{
		CF_Trace trace(this, "SetModel", "" + model);

		CF_Map<string, ref CF_MVVM_Property> allProps = new CF_Map<string, ref CF_MVVM_Property>();

		_SetModel(model, allProps);

		CF_MVVM._LoadPropertyTypes(m_Model, this, allProps);
	}

	void _SetModel(CF_ModelBase model, CF_Map<string, ref CF_MVVM_Property> allProps)
	{
		CF_Trace trace(this, "_SetModel", "" + model);

		m_Model = model;

		if (m_Model)
		{
			m_Widget.SetUserData(model);
			m_Widget.SetHandler(this);

			m_TempProperties = allProps;

			GetProperties();

			m_TempProperties = null;

			set<CF_ViewModel> children = GetChildren();
			for (int i = 0; i < children.Count(); i++)
			{
				children[i]._SetModel(model, allProps);
			}
		}
	}

	protected void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		AddProperty(Children, "Children");
	}
	
	protected void AddProperty(string actual, string name)
	{
		CF_Trace trace(this, "AddProperty", "Actual=" + actual + " Name=" + name);
		
		if (actual == string.Empty) return;
		CF_MVVM_Property property = new CF_MVVM_Property(this, name);
		m_Properties.Insert(actual, property);
		m_TempProperties.Insert(actual, property);
	}

	Widget GetChildWidgetAt(int index)
	{
		CF_Trace trace(this, "GetChildWidgetAt", "" + index);

		if (index == 0) return null;

		Widget widget = m_Widget.GetChildren();
		for (int i = 1; i < index; i++)
		{
			widget = widget.GetSibling();
			if (!widget) return null;
		}
		return widget;
	}

	Widget GetWidget()
	{
		return m_Widget;
	}

	set<CF_ViewModel> GetChildren()
	{
		return m_Children;
	}

	void AddChild(CF_ViewModel child, bool modifyParent = true)
	{
		CF_Trace trace(this, "AddChild", "" + child, "" + modifyParent);

		m_Children.Insert(child);
		if (modifyParent) child.SetParent(this, false);
	}

	void RemoveChild(CF_ViewModel child, bool modifyParent = true)
	{
		CF_Trace trace(this, "RemoveChild", "" + child, "" + modifyParent);

		for (int i = 0; i < m_Children.Count(); i++)
		{
			if (m_Children[i] == child)
			{
				if (modifyParent) child.SetParent(null, false);
				m_Children.Remove(i);
				return;
			}
		}
	}

	void SetParent(CF_ViewModel parent, bool modifyParent = true)
	{
		CF_Trace trace(this, "SetParent", "" + parent, "" + modifyParent);

		//! if the parent remains unchanged, don't continue execution
		if (m_Parent == parent) return;

		//! remove us from the old parent if it exists
		if (m_Parent) m_Parent.RemoveChild(this, false);

		//! update the parent
		m_Parent = parent;
		
		//! add us to the new parent. only called if the new parent didn't call this
		if (m_Parent && modifyParent) m_Parent.AddChild(this, false);
	}

	/**
	 * @section	Children
	 * 
	 * @note	
	 */
	void OnView_Children(Class sender, CF_EventArgs args)
	{
		// Handled automatically.
	}

	void OnModel_Children(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children", "" + sender, args.ClassName());

		CF_ObservableCollection _collection;
		EnScript.GetClassVar(m_Model, Children, 0, _collection);
		if (!_collection) return;

		CF_CollectionEventArgs cevt;
		if (Class.CastTo(cevt, args))
		{
			cevt.Process(this, m_Model, _collection);
			return;
		}

		OnModel_Children_InsertAll(_collection, args);
	}

	void OnModel_Children_InsertAll(CF_ObservableCollection sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAll", "" + sender);

		for (int i = 0; i < sender.Count(); i++)
		{
			CF_TypeConverter conv = sender.GetConverter(i);
			if (!conv) return;

			CF_ModelBase model = conv.GetManaged();
			
			string layout;
			g_Script.CallFunction(model, "GetLayout", layout, null);
			if (layout == string.Empty)
			{
				CF.Log.Error("Empty layout file provided.");
				return;
			}

			CF_MVVM.Create(model, layout, m_Widget);
		}
	}

	void OnModel_Children_Insert(CF_ObservableCollection sender, CF_CollectionInsertEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_Insert", "" + sender, args.ToStr());

		CF_TypeConverter conv = sender.GetConverter(args.Index);
		if (!conv) return;

		CF_ModelBase model = conv.GetManaged();
		
		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		if (layout == string.Empty)
		{
			CF.Log.Error("Empty layout file provided.");
			return;
		}
		
		CF_MVVM.Create(model, layout, m_Widget);
	}

	void OnModel_Children_InsertAt(CF_ObservableCollection sender, CF_CollectionInsertAtEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + sender, args.ToStr());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Clear(CF_ObservableCollection sender, CF_CollectionClearEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_Clear", "" + sender, args.ToStr());

		Widget child = m_Widget.GetChildren();
		while (child != null)
		{
			Widget current = child;
			child = child.GetSibling();

			CF_ModelBase model;
			current.GetUserData(model);
			if (model)
			{
				CF_MVVM.Destroy(model);
			}
		}
	}

	void OnModel_Children_Set(CF_ObservableCollection sender, CF_CollectionSetEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_Set", "" + sender, args.ToStr());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Remove(CF_ObservableCollection sender, CF_CollectionRemoveEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_Remove", "" + sender, args.ToStr());

		Widget widget = GetChildWidgetAt(args.Index);
		if (!widget) return;

		m_Widget.RemoveChild(widget);
	}

	void OnModel_Children_Swap(CF_ObservableCollection sender, CF_CollectionSwapEventArgs args)
	{
		CF_Trace trace(this, "OnModel_Children_Swap", "" + sender, args.ToStr());

		CF.Log.Error("Function not implemented");
	}

	/**
	 * @section	Events
	 * 
	 * @note	Continue is handled in the script widget instead of 'CF_ViewModel' as some 
	 * 			events require reverse cancellation. For example, if 'Continue' is set to 'false'
	 * 			for 'OnChange' in 'CF_EditBoxWidget', then input must be prevented.
	 */
	bool OnClick(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnModalResult(Class sender, CF_ModalEventArgs args) { return true; }
	bool OnDoubleClick(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnSelect(Class sender, CF_SelectEventArgs args) { return true; }
	bool OnItemSelected(Class sender, CF_ItemSelectEventArgs args) { return true; }
	bool OnFocus(Class sender, CF_PositionEventArgs args) { return true; }
	bool OnFocusLost(Class sender, CF_PositionEventArgs args) { return true; }
	bool OnMouseEnter(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnMouseLeave(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnMouseWheel(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnMouseButtonDown(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnMouseButtonUp(Class sender, CF_MouseEventArgs args) { return true; }
	bool OnController(Class sender, CF_ControllerEventArgs args) { return true; }
	bool OnKeyDown(Class sender, CF_KeyEventArgs args) { return true; }
	bool OnKeyUp(Class sender, CF_KeyEventArgs args) { return true; }
	bool OnKeyPress(Class sender, CF_KeyEventArgs args) { return true; }
	bool OnChange(Class sender, CF_ChangeEventArgs args) { return true; }
	bool OnDrag(Class sender, CF_DragEventArgs args) { return true; }
	bool OnDragging(Class sender, CF_DragEventArgs args) { return true; }
	bool OnDraggingOver(Class sender, CF_DragEventArgs args) { return true; }
	bool OnDrop(Class sender, CF_DragEventArgs args) { return true; }
	bool OnDropReceived(Class sender, CF_DragEventArgs args) { return true; }
	bool OnResize(Class sender, CF_ResizeEventArgs args) { return true; }
	bool OnChildAdd(Class sender, CF_ChildEventArgs args) { return true; }
	bool OnChildRemove(Class sender, CF_ChildEventArgs args) { return true; }
	bool OnUpdate(Class sender, CF_ViewEventArgs args) { return true; }

	override bool OnClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnClick", "" + w);

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_Click != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Click, null, param);
		}

		return OnClick(this, args);
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		CF_Trace trace(this, "OnModalResult", "" + w);

		CF_ModalEventArgs args = new CF_ModalEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Code = code;
		args.Result = result;

		if (Event_ModalResult != string.Empty)
		{
			Param param = new Param2<Class, CF_ModalEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_ModalResult, null, param);
		}

		return OnModalResult(this, args);
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnDoubleClick", "" + w);
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_DoubleClick != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_DoubleClick, null, param);
		}

		return OnDoubleClick(this, args);
	}
	
	override bool OnSelect(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnSelect", "" + w);

		CF_SelectEventArgs args = new CF_SelectEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Select != string.Empty)
		{
			Param param = new Param2<Class, CF_SelectEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Select, null, param);
		}

		return OnSelect(this, args);
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		CF_Trace trace(this, "OnItemSelected", "" + w);

		CF_ItemSelectEventArgs args = new CF_ItemSelectEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Row = row;
		args.Column = column;
		args.OldRow = oldRow;
		args.OldColumn = oldColumn;

		if (Event_ItemSelected != string.Empty)
		{
			Param param = new Param2<Class, CF_ItemSelectEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_ItemSelected, null, param);
		}

		return OnItemSelected(this, args);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocus", "" + w);

		CF_PositionEventArgs args = new CF_PositionEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Focus != string.Empty)
		{
			Param param = new Param2<Class, CF_PositionEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Focus, null, param);
		}

		return OnFocus(this, args);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnFocusLost", "" + w);
		
		CF_PositionEventArgs args = new CF_PositionEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_FocusLost != string.Empty)
		{
			Param param = new Param2<Class, CF_PositionEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_FocusLost, null, param);
		}

		return OnFocusLost(this, args);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnMouseEnter", "" + w);

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Type = 1;

		if (Event_MouseEnter != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseEnter, null, param);
		}

		return OnMouseEnter(this, args);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		CF_Trace trace(this, "OnMouseLeave", "" + w);

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Enter = enterW;
		args.Type = 2;

		if (Event_MouseLeave != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseLeave, null, param);
		}

		return OnMouseLeave(this, args);
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		CF_Trace trace(this, "OnMouseWheel", "" + w);

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Wheel = wheel;

		if (Event_MouseWheel != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseWheel, null, param);
		}

		return OnMouseWheel(this, args);
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonDown", "" + w);
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_MouseButtonDown != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonDown, null, param);
		}

		return OnMouseButtonDown(this, args);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		CF_Trace trace(this, "OnMouseButtonUp", "" + w);
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_MouseButtonUp != string.Empty)
		{
			Param param = new Param2<Class, CF_MouseEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonUp, null, param);
		}

		return OnMouseButtonUp(this, args);
	}

	override bool OnController(Widget w, int control, int value)
	{
		CF_Trace trace(this, "OnController", "" + w);

		CF_ControllerEventArgs args = new CF_ControllerEventArgs();
		args.Target = w;
		args.Control = control;
		args.Value = value;

		if (Event_Controller == string.Empty)
		{
			Param param = new Param2<Class, CF_ControllerEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Controller, null, param);
		}

		return OnController(this, args);
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyDown", "" + w);
		
		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.DOWN;

		if (Event_KeyDown != string.Empty)
		{
			Param param = new Param2<Class, CF_KeyEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyDown, null, param);
		}

		return OnKeyDown(this, args);
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyUp", "" + w);

		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.UP;

		if (Event_KeyUp != string.Empty)
		{
			Param param = new Param2<Class, CF_KeyEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyUp, null, param);
		}

		return OnKeyUp(this, args);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		CF_Trace trace(this, "OnKeyPress", "" + w);

		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.PRESS;

		if (Event_KeyPress != string.Empty)
		{
			Param param = new Param2<Class, CF_KeyEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyPress, null, param);
		}

		return OnKeyPress(this, args);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		CF_Trace trace(this, "OnChange", "" + w);
		
		CF_ChangeEventArgs args = new CF_ChangeEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Finished = finished;

		if (Event_Change != string.Empty)
		{
			Param param = new Param2<Class, CF_ChangeEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Change, null, param);
		}

		return OnChange(this, args);
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnDrag", "" + w);
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = null;

		if (Event_Drag != string.Empty)
		{
			Param param = new Param2<Class, CF_DragEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Drag, null, param);
		}

		return OnDrag(this, args);
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDragging", "" + w);
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_Dragging != string.Empty)
		{
			Param param = new Param2<Class, CF_DragEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Dragging, null, param);
		}

		return OnDragging(this, args);
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDraggingOver", "" + w);
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_DraggingOver != string.Empty)
		{
			Param param = new Param2<Class, CF_DragEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_DraggingOver, null, param);
		}

		return OnDraggingOver(this, args);
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDrop", "" + w);

		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_Drop != string.Empty)
		{
			Param param = new Param2<Class, CF_DragEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Drop, null, param);
		}

		return OnDrop(this, args);
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		CF_Trace trace(this, "OnDropReceived", "" + w);

		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_DropReceived != string.Empty)
		{
			Param param = new Param2<Class, CF_DragEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_DropReceived, null, param);
		}

		return OnDropReceived(this, args);
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		CF_Trace trace(this, "OnResize", "" + w);

		CF_ResizeEventArgs args = new CF_ResizeEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Resize != string.Empty)
		{
			Param param = new Param2<Class, CF_ResizeEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Resize, null, param);
		}

		return OnResize(this, args);
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildAdd", "" + w);

		CF_ChildEventArgs args = new CF_ChildEventArgs();
		args.Target = w;
		args.Child = child;
		args.Remove = false;

		if (Event_ChildAdd != string.Empty)
		{
			Param param = new Param2<Class, CF_ChildEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_ChildAdd, null, param);
		}

		return OnChildAdd(this, args);
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		CF_Trace trace(this, "OnChildRemove", "" + w);

		CF_ChildEventArgs args = new CF_ChildEventArgs();
		args.Target = w;
		args.Child = child;
		args.Remove = true;

		if (Event_ChildRemove != string.Empty)
		{
			Param param = new Param2<Class, CF_ChildEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_ChildRemove, null, param);
		}

		return OnChildRemove(this, args);
	}
	
	override bool OnUpdate(Widget w)
	{
		CF_Trace trace(this, "OnUpdate", "" + w);

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Update != string.Empty)
		{
			Param param = new Param2<Class, CF_ViewEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Update, null, param);
		}

		return OnUpdate(this, args);
	}
	
	bool OnShow(Widget w)
	{
		CF_Trace trace(this, "OnShow", "" + w);

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Show != string.Empty)
		{
			Param param = new Param2<Class, CF_ViewEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Show, null, param);
		}

		return true;
	}
	
	bool OnHide(Widget w)
	{
		CF_Trace trace(this, "OnHide", "" + w);

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Hide != string.Empty)
		{
			Param param = new Param2<Class, CF_ViewEventArgs>(this, args);
			g_Script.CallFunctionParams(m_Model, Event_Hide, null, param);
		}

		return true;
	}
};