class CF_MVVM_View : ScriptedWidgetEventHandler
{
	reference string Model;
	reference string Children;

	protected Widget m_Widget;

    #ifdef COMPONENT_SYSTEM 
	private ref CF_ModelBase m_WB_Model;
	#endif

	//! In-game, the ref count shouldn't be incremented. When the ref count == 0, then this view should be destroyed.
	protected CF_ModelBase m_Model;

	//! Lifetimes are managed by the enfusion widgets
	protected CF_MVVM_View m_Parent = null;
	protected ref set<CF_MVVM_View> m_Children = new set<CF_MVVM_View>();

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
				CF_MVVM_View view = null;
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

	void ~CF_MVVM_View()
	{
		CF_Trace trace(this, "~CF_MVVM_View");
	}

	void NotifyPropertyChanged(string name, CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, "" + temp);

		CF_MVVM_Property property;
		if (!m_Properties.Find(name, property)) return;

		property.OnView(temp);
	}

	void NotifyPropertyChanged(CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(this, "NotifyPropertyChanged", "" + temp.ToStr());

		for (int i = 0; i < m_Properties.Count(); i++)
		{
			m_Properties.GetElement(i).OnView(temp);
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

			set<CF_MVVM_View> children = GetChildren();
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

	Widget GetWidget()
	{
		return m_Widget;
	}

	set<CF_MVVM_View> GetChildren()
	{
		return m_Children;
	}

	void AddChild(CF_MVVM_View child, bool modifyParent = true)
	{
		CF_Trace trace(this, "AddChild", "" + child, "" + modifyParent);

		m_Children.Insert(child);
		if (modifyParent) child.SetParent(this, false);
	}

	void RemoveChild(CF_MVVM_View child, bool modifyParent = true)
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

	void SetParent(CF_MVVM_View parent, bool modifyParent = true)
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
	void OnView_Children(CF_ModelBase model, CF_EventArgs evt)
	{
		// Handled automatically.
	}

	void OnModel_Children(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children", "" + model, evt.ClassName());

		CF_ObservableCollection _collection;
		EnScript.GetClassVar(model, Children, 0, _collection);
		if (!_collection) return;

		CF_CollectionEventArgs cevt;
		if (Class.CastTo(cevt, evt))
		{
			cevt.Process(this, model, _collection);
			return;
		}

		OnModel_Children_InsertAll(_collection);
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

	void OnModel_Children_InsertAll(CF_ObservableCollection collection)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAll", "" + collection);

		for (int i = 0; i < collection.Count(); i++)
		{
			CF_TypeConverter conv = collection.GetConverter(i);
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

	void OnModel_Children_Insert(CF_ObservableCollection collection, CF_CollectionInsertEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Insert", "" + collection, evt.ToStr());

		CF_TypeConverter conv = collection.GetConverter(evt.Index);
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

	void OnModel_Children_InsertAt(CF_ObservableCollection collection, CF_CollectionInsertAtEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + collection, evt.ToStr());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Clear(CF_ObservableCollection collection, CF_CollectionClearEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Clear", "" + collection, evt.ToStr());

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

	void OnModel_Children_Set(CF_ObservableCollection collection, CF_CollectionSetEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Set", "" + collection, evt.ToStr());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Remove(CF_ObservableCollection collection, CF_CollectionRemoveEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Remove", "" + collection, evt.ToStr());

		Widget widget = GetChildWidgetAt(evt.Index);
		if (!widget) return;

		m_Widget.RemoveChild(widget);
	}

	void OnModel_Children_Swap(CF_ObservableCollection collection, CF_CollectionSwapEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Swap", "" + collection, evt.ToStr());

		CF.Log.Error("Function not implemented");
	}

	/**
	 * @section	Events
	 * 
	 * @note	Continue is handled in the script widget instead of 'CF_ViewModel' as some 
	 * 			events require reverse cancellation. For example, if 'Continue' is set to 'false'
	 * 			for 'OnChange' in 'CF_EditBoxWidget', then input must be prevented.
	 */
	bool OnClick(CF_MouseEventArgs evt) { return true; }
	bool OnModalResult(CF_ModalEventArgs evt) { return true; }
	bool OnDoubleClick(CF_MouseEventArgs evt) { return true; }
	bool OnSelect(CF_SelectEventArgs evt) { return true; }
	bool OnItemSelected(CF_ItemSelectEventArgs evt) { return true; }
	bool OnFocus(CF_PositionEventArgs evt) { return true; }
	bool OnFocusLost(CF_PositionEventArgs evt) { return true; }
	bool OnMouseEnter(CF_MouseEventArgs evt) { return true; }
	bool OnMouseLeave(CF_MouseEventArgs evt) { return true; }
	bool OnMouseWheel(CF_MouseEventArgs evt) { return true; }
	bool OnMouseButtonDown(CF_MouseEventArgs evt) { return true; }
	bool OnMouseButtonUp(CF_MouseEventArgs evt) { return true; }
	bool OnController(CF_ControllerEventArgs evt) { return true; }
	bool OnKeyDown(CF_KeyEventArgs evt) { return true; }
	bool OnKeyUp(CF_KeyEventArgs evt) { return true; }
	bool OnKeyPress(CF_KeyEventArgs evt) { return true; }
	bool OnChange(CF_ChangeEventArgs evt) { return true; }
	bool OnDrag(CF_DragEventArgs evt) { return true; }
	bool OnDragging(CF_DragEventArgs evt) { return true; }
	bool OnDraggingOver(CF_DragEventArgs evt) { return true; }
	bool OnDrop(CF_DragEventArgs evt) { return true; }
	bool OnDropReceived(CF_DragEventArgs evt) { return true; }
	bool OnResize(CF_ResizeEventArgs evt) { return true; }
	bool OnChildAdd(CF_ChildEventArgs evt) { return true; }
	bool OnChildRemove(CF_ChildEventArgs evt) { return true; }
	bool OnUpdate(CF_ViewEventArgs evt) { return true; }
};
