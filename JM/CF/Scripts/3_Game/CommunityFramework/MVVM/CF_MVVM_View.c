class CF_MVVM_View
{
	reference string Model;
	reference string Children;

	protected Widget m_Widget;

    #ifdef COMPONENT_SYSTEM 
	protected ref CF_ViewModel m_ViewModel;
	private ref Managed m_Model;
	#else
	//! In-game, the ref count shouldn't be incremented. When the ref count == 0, then this view should be destroyed.
	protected CF_ViewModel m_ViewModel;
	#endif

	private bool m_IsRoot;

	//! Lifetimes are managed by the enfusion widgets
	protected CF_MVVM_View m_Parent = null;
	protected ref set<CF_MVVM_View> m_Children = new set<CF_MVVM_View>();

	protected ref array<ref CF_MVVM_Property> m_Properties;
	protected map<string, ref CF_MVVM_Property> m_PropertiesMap;

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
				if (!CF.MVVM.WB_NEXT_IN_SCRIPT)
				{
					Class.CastTo(m_Model, modelType.Spawn());
					m_ViewModel = new CF_ViewModel(this, m_Model);
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

		//! If not in workbench editing
    	#ifndef COMPONENT_SYSTEM
		if (CF.MVVM && m_ViewModel && m_IsRoot) CF.MVVM._Destroy(m_ViewModel);
		#endif
	}

	bool IsBinded(CF_ViewModel vm)
	{
		return m_ViewModel == vm;
	}

	void NotifyPropertyChanged(string name, CF_EventArgs evt = null)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + name);

		if (!m_ViewModel) return;

		m_ViewModel.NotifyViewPropertyChanged(name, evt);
	}

	void GetProperties(CF_ViewModel viewModel, inout map<string, ref CF_MVVM_Property> propertiesMap, inout array<ref CF_MVVM_Property> properties)
	{
		CF_Trace trace(this, "GetProperties", "" + viewModel, "" + propertiesMap, "" + properties);
		
		m_ViewModel = viewModel;
		m_Widget.SetUserData(m_ViewModel);
		m_Widget.SetHandler(m_ViewModel);

		m_Properties = properties;
		m_PropertiesMap = propertiesMap;

		GetProperties();

		m_Properties = null;
		m_PropertiesMap = null;
	}

	void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		AddProperty(Children, "Children");
	}
	
	protected void AddProperty(string actual, string name)
	{
		CF_Trace trace(this, "AddProperty", "Actual=" + actual + " Name=" + name);
		
		if (actual == string.Empty) return;
		CF_MVVM_Property property = new CF_MVVM_Property(this, name);
		m_Properties.Insert(property);
		m_PropertiesMap.Insert(actual, property);
	}
	
	void SetViewModel(CF_ViewModel viewModel)
	{
		CF_Trace trace(this, "SetViewModel", "" + viewModel);

		m_ViewModel = viewModel;
		m_Widget.SetUserData(m_ViewModel);
		m_Widget.SetHandler(m_ViewModel);

		m_IsRoot = false;
		if (m_ViewModel) m_IsRoot = true;
	}

	CF_ViewModel GetViewModel()
	{
		return m_ViewModel;
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

			CF.MVVM.Create(model, layout, m_Widget);
		}
	}

	void OnModel_Children_Insert(CF_ObservableCollection collection, CF_CollectionInsertEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Insert", "" + collection, evt.String());

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
		
		CF.MVVM.Create(model, layout, m_Widget);
	}

	void OnModel_Children_InsertAt(CF_ObservableCollection collection, CF_CollectionInsertAtEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_InsertAt", "" + collection, evt.String());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Clear(CF_ObservableCollection collection, CF_CollectionClearEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Clear", "" + collection, evt.String());

		Widget child = m_Widget.GetChildren();
		while (child != null)
		{
			Widget current = child;
			child = child.GetSibling();

			CF_ViewModel vm;
			current.GetUserData(vm);
			if (vm)
			{
				CF.MVVM._Destroy(vm);
			}
		}
	}

	void OnModel_Children_Set(CF_ObservableCollection collection, CF_CollectionSetEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Set", "" + collection, evt.String());

		CF.Log.Error("Function not implemented");
	}

	void OnModel_Children_Remove(CF_ObservableCollection collection, CF_CollectionRemoveEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Remove", "" + collection, evt.String());

		Widget widget = GetChildWidgetAt(evt.Index);
		if (!widget) return;

		m_Widget.RemoveChild(widget);
	}

	void OnModel_Children_Swap(CF_ObservableCollection collection, CF_CollectionSwapEventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Children_Swap", "" + collection, evt.String());

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
