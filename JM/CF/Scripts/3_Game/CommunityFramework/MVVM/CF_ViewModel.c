class CF_ViewModel : ScriptedWidgetEventHandler
{
	reference string Model;
	reference bool CreateModel = false;
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

    //#ifdef COMPONENT_SYSTEM 
	private ref CF_ModelBase m_WB_Model;
	//#endif

	//! In-game, the ref count shouldn't be incremented. When the ref count == 0, then this view should be destroyed.
	protected CF_ModelBase m_Model;

	//! Lifetimes are managed by the enfusion widgets
	protected CF_ViewModel m_Parent = null;
	protected ref set<CF_ViewModel> m_Children = new set<CF_ViewModel>();

	protected autoptr map<string, ref CF_MVVM_Property> m_PropertiesSourceMap = new map<string, ref CF_MVVM_Property>();
	protected ref CF_MVVM_Linker m_Properties;
	
	void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		m_Widget = w;
		
		m_Widget.SetHandler(this);

		if (Model != string.Empty)
		{
			typename modelType = Model.ToType();
			if (modelType)
			{
    			#ifdef COMPONENT_SYSTEM //! Workbench editing
				if (!CF_MVVM.WB_NEXT_IN_SCRIPT)
				#else
				if (CreateModel)
				#endif
				{
					Class.CastTo(m_WB_Model, modelType.Spawn());
					CF_MVVM.Connect(m_WB_Model, this);
				}
			}
			else
			{
				Model = string.Empty;
			}
		}

		if (Model == string.Empty)
		{
			Widget parent = m_Widget.GetParent();
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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_ViewModel");
		#endif
	}

	void NotifyPropertyChanged(string name, string source, CF_EventArgs args = null)
	{
		CF_EventArgs temp = args;
		if (temp == null) temp = new CF_EventArgs();

		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, "" + temp);
		#endif
		
		auto property = m_PropertiesSourceMap[source];
		if (!property) return;
		property.OnView(temp);

		m_Properties._ViewChanged(name, property, temp);
	}

	void NotifyPropertyChanged(CF_EventArgs args = null)
	{
		CF_EventArgs temp = args;
		if (temp == null) temp = new CF_EventArgs();

		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "NotifyPropertyChanged", "" + temp.ToStr());
		#endif

		m_Properties._ViewChanged(temp);
	}

	void _RecursiveSetModel(CF_ModelBase model, CF_MVVM_Linker properties)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "_RecursiveSetModel", "" + model);
		#endif

		m_Model = model;
		m_Properties = properties;

		if (m_Model)
		{
			m_Widget.SetUserData(m_Model);

			GetProperties();

			set<CF_ViewModel> children = GetChildren();
			for (int i = 0; i < children.Count(); i++)
			{
				children[i]._RecursiveSetModel(m_Model, m_Properties);
			}
		}
	}

	protected void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		AddProperty(Children, "Children");
	}
	
	protected void AddProperty(inout string actual, string name)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "AddProperty", "Actual=" + actual + " Name=" + name);
		#endif
		
		if (actual == string.Empty) return;

		CF_MVVM_Property property = new CF_MVVM_Property(this, name);
		actual = property.SetVariableName(actual);
		
		m_PropertiesSourceMap.Insert(name, property);
		m_Properties.Insert(property);
	}

	Widget GetChildWidgetAt(int index)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetChildWidgetAt", "" + index);
		#endif

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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "AddChild", "" + child, "" + modifyParent);
		#endif

		m_Children.Insert(child);
		if (modifyParent) child.SetParent(this, false);
	}

	void RemoveChild(CF_ViewModel child, bool modifyParent = true)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "RemoveChild", "" + child, "" + modifyParent);
		#endif

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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetParent", "" + parent, "" + modifyParent);
		#endif

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
	void OnView_Children(CF_ModelBase sender, CF_EventArgs args)
	{
		// Handled automatically.
	}

	void OnModel_Children(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children", "" + sender, args.ClassName());
		#endif

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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_InsertAll", "" + sender);
		#endif

		for (int i = 0; i < sender.Count(); i++)
		{
			CF_TypeConverter conv = sender.GetConverter(i);
			if (!conv) return;

			CF_ModelBase model = conv.GetManaged();
			
			string layout;
			g_Script.CallFunction(model, "GetLayout", layout, null);
			if (layout == string.Empty)
			{
				CF_Log.Error("Empty layout file provided.");
				return;
			}

			CF_MVVM.Create(model, layout, m_Widget);
		}
	}

	void OnModel_Children_Insert(CF_ObservableCollection sender, CF_CollectionInsertEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Insert", "" + sender, args.ToStr());
		#endif

		CF_TypeConverter conv = sender.GetConverter(args.Index);
		if (!conv) return;

		CF_ModelBase model = conv.GetManaged();
		
		string layout;
		g_Script.CallFunction(model, "GetLayout", layout, null);
		if (layout == string.Empty)
		{
			CF_Log.Error("Empty layout file provided.");
			return;
		}
		
		CF_MVVM.Create(model, layout, m_Widget);
	}

	void OnModel_Children_InsertAt(CF_ObservableCollection sender, CF_CollectionInsertAtEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + sender, args.ToStr());
		#endif

		CF_Log.Error("Function not implemented");
	}

	void OnModel_Children_Clear(CF_ObservableCollection sender, CF_CollectionClearEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Clear", "" + sender, args.ToStr());
		#endif

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
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Set", "" + sender, args.ToStr());
		#endif

		CF_Log.Error("Function not implemented");
	}

	void OnModel_Children_Remove(CF_ObservableCollection sender, CF_CollectionRemoveEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Remove", "" + sender, args.ToStr());
		#endif

		Widget widget = GetChildWidgetAt(args.Index);
		if (!widget) return;

		m_Widget.RemoveChild(widget);
	}

	void OnModel_Children_Swap(CF_ObservableCollection sender, CF_CollectionSwapEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Children_Swap", "" + sender, args.ToStr());
		#endif

		CF_Log.Error("Function not implemented");
	}

	bool WhatChanged(out string name, out string variable)
	{
		return false;
	}

	/**
	 * @section	Events
	 * 
	 * @note	Continue is handled in the script widget instead of 'CF_ViewModel' as some 
	 * 			events require reverse cancellation. For example, if 'Continue' is set to 'false'
	 * 			for 'OnChange' in 'CF_EditBoxWidget', then input must be prevented.
	 */
	bool OnClick(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnModalResult(CF_ModelBase sender, CF_ModalEventArgs args) { return !args.Continue; }
	bool OnDoubleClick(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnSelect(CF_ModelBase sender, CF_SelectEventArgs args) { return !args.Continue; }
	bool OnItemSelected(CF_ModelBase sender, CF_ItemSelectEventArgs args) { return !args.Continue; }
	bool OnFocus(CF_ModelBase sender, CF_PositionEventArgs args) { return !args.Continue; }
	bool OnFocusLost(CF_ModelBase sender, CF_PositionEventArgs args) { return !args.Continue; }
	bool OnMouseEnter(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnMouseLeave(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnMouseWheel(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnMouseButtonDown(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnMouseButtonUp(CF_ModelBase sender, CF_MouseEventArgs args) { return !args.Continue; }
	bool OnController(CF_ModelBase sender, CF_ControllerEventArgs args) { return !args.Continue; }
	bool OnKeyDown(CF_ModelBase sender, CF_KeyEventArgs args) { return !args.Continue; }
	bool OnKeyUp(CF_ModelBase sender, CF_KeyEventArgs args) { return !args.Continue; }
	bool OnKeyPress(CF_ModelBase sender, CF_KeyEventArgs args) { return !args.Continue; }
	bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args) { return !args.Continue; }
	bool OnDrag(CF_ModelBase sender, CF_DragEventArgs args) { return !args.Continue; }
	bool OnDragging(CF_ModelBase sender, CF_DragEventArgs args) { return !args.Continue; }
	bool OnDraggingOver(CF_ModelBase sender, CF_DragEventArgs args) { return !args.Continue; }
	bool OnDrop(CF_ModelBase sender, CF_DragEventArgs args) { return !args.Continue; }
	bool OnDropReceived(CF_ModelBase sender, CF_DragEventArgs args) { return !args.Continue; }
	bool OnResize(CF_ModelBase sender, CF_ResizeEventArgs args) { return !args.Continue; }
	bool OnChildAdd(CF_ModelBase sender, CF_ChildEventArgs args) { return !args.Continue; }
	bool OnChildRemove(CF_ModelBase sender, CF_ChildEventArgs args) { return !args.Continue; }
	bool OnUpdate(CF_ModelBase sender, CF_ViewEventArgs args) { return !args.Continue; }

	override bool OnClick(Widget w, int x, int y, int button)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnClick", "" + w);
		#endif

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_Click != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Click, null, param);
		}

		return OnClick(this, args);
	}

	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModalResult", "" + w);
		#endif

		CF_ModalEventArgs args = new CF_ModalEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Code = code;
		args.Result = result;

		if (Event_ModalResult != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ModalEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_ModalResult, null, param);
		}

		return OnModalResult(this, args);
	}

	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDoubleClick", "" + w);
		#endif
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_DoubleClick != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_DoubleClick, null, param);
		}

		return OnDoubleClick(this, args);
	}
	
	override bool OnSelect(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnSelect", "" + w);
		#endif

		CF_SelectEventArgs args = new CF_SelectEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Select != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_SelectEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Select, null, param);
		}

		return OnSelect(this, args);
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnItemSelected", "" + w);
		#endif

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
			Param param = new Param2<CF_ModelBase, CF_ItemSelectEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_ItemSelected, null, param);
		}

		return OnItemSelected(this, args);
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnFocus", "" + w);
		#endif

		CF_PositionEventArgs args = new CF_PositionEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Focus != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_PositionEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Focus, null, param);
		}

		return OnFocus(this, args);
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnFocusLost", "" + w);
		#endif
		
		CF_PositionEventArgs args = new CF_PositionEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_FocusLost != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_PositionEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_FocusLost, null, param);
		}

		return OnFocusLost(this, args);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseEnter", "" + w);
		#endif

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Type = 1;

		if (Event_MouseEnter != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseEnter, null, param);
		}

		return OnMouseEnter(this, args);
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseLeave", "" + w);
		#endif

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Enter = enterW;
		args.Type = 2;

		if (Event_MouseLeave != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseLeave, null, param);
		}

		return OnMouseLeave(this, args);
	}
	
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseWheel", "" + w);
		#endif

		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = -1;
		args.Wheel = wheel;

		if (Event_MouseWheel != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseWheel, null, param);
		}

		return OnMouseWheel(this, args);
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseButtonDown", "" + w);
		#endif
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_MouseButtonDown != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonDown, null, param);
		}

		return OnMouseButtonDown(this, args);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnMouseButtonUp", "" + w);
		#endif
		
		CF_MouseEventArgs args = new CF_MouseEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Button = button;

		if (Event_MouseButtonUp != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_MouseEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_MouseButtonUp, null, param);
		}

		return OnMouseButtonUp(this, args);
	}

	override bool OnController(Widget w, int control, int value)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnController", "" + w);
		#endif

		CF_ControllerEventArgs args = new CF_ControllerEventArgs();
		args.Target = w;
		args.Control = control;
		args.Value = value;

		if (Event_Controller == string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ControllerEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Controller, null, param);
		}

		return OnController(this, args);
	}
	
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnKeyDown", "" + w);
		#endif
		
		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.DOWN;

		if (Event_KeyDown != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_KeyEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyDown, null, param);
		}

		return OnKeyDown(this, args);
	}
	
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnKeyUp", "" + w);
		#endif

		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.UP;

		if (Event_KeyUp != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_KeyEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyUp, null, param);
		}

		return OnKeyUp(this, args);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnKeyPress", "" + w);
		#endif

		CF_KeyEventArgs args = new CF_KeyEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Key = key;
		args.State = CF_KeyState.PRESS;

		if (Event_KeyPress != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_KeyEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_KeyPress, null, param);
		}

		return OnKeyPress(this, args);
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", "" + w);
		#endif
		
		CF_ChangeEventArgs args = new CF_ChangeEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Finished = finished;

		string name;
		if (WhatChanged(name, args.Changed))
		{
			NotifyPropertyChanged(args.Changed, name);
		}

		if (Event_Change != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ChangeEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Change, null, param);
		}

		return OnChange(this, args);
	}
	
	override bool OnDrag(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDrag", "" + w);
		#endif
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = null;

		if (Event_Drag != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_DragEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Drag, null, param);
		}

		return OnDrag(this, args);
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDragging", "" + w);
		#endif
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_Dragging != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_DragEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Dragging, null, param);
		}

		return OnDragging(this, args);
	}
	
	override bool OnDraggingOver(Widget w, int x, int y, Widget reciever)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDraggingOver", "" + w);
		#endif
		
		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_DraggingOver != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_DragEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_DraggingOver, null, param);
		}

		return OnDraggingOver(this, args);
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDrop", "" + w);
		#endif

		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_Drop != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_DragEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Drop, null, param);
		}

		return OnDrop(this, args);
	}
	
	override bool OnDropReceived(Widget w, int x, int y, Widget reciever)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDropReceived", "" + w);
		#endif

		CF_DragEventArgs args = new CF_DragEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;
		args.Reciever = reciever;

		if (Event_DropReceived != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_DragEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_DropReceived, null, param);
		}

		return OnDropReceived(this, args);
	}
	
	override bool OnResize(Widget w, int x, int y)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnResize", "" + w);
		#endif

		CF_ResizeEventArgs args = new CF_ResizeEventArgs();
		args.Target = w;
		args.X = x;
		args.Y = y;

		if (Event_Resize != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ResizeEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Resize, null, param);
		}

		return OnResize(this, args);
	}
	
	override bool OnChildAdd(Widget w, Widget child)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChildAdd", "" + w);
		#endif

		CF_ChildEventArgs args = new CF_ChildEventArgs();
		args.Target = w;
		args.Child = child;
		args.Remove = false;

		if (Event_ChildAdd != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ChildEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_ChildAdd, null, param);
		}

		return OnChildAdd(this, args);
	}
	
	override bool OnChildRemove(Widget w, Widget child)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChildRemove", "" + w);
		#endif

		CF_ChildEventArgs args = new CF_ChildEventArgs();
		args.Target = w;
		args.Child = child;
		args.Remove = true;

		if (Event_ChildRemove != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ChildEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_ChildRemove, null, param);
		}

		return OnChildRemove(this, args);
	}
	
	override bool OnUpdate(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnUpdate", "" + w);
		#endif

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Update != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ViewEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Update, null, param);
		}

		return OnUpdate(this, args);
	}
	
	bool OnShow(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnShow", "" + w);
		#endif

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Show != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ViewEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Show, null, param);
		}

		return true;
	}
	
	bool OnHide(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnHide", "" + w);
		#endif

		CF_ViewEventArgs args = new CF_ViewEventArgs();
		args.Target = w;

		if (Event_Hide != string.Empty)
		{
			Param param = new Param2<CF_ModelBase, CF_ViewEventArgs>(null, args);
			g_Script.CallFunctionParams(m_Model, Event_Hide, null, param);
		}

		return true;
	}
};