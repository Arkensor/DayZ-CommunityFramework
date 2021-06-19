class CF_MVVM_View
{
	reference string Model;
	reference string Children;

	private Widget m_Widget;

    #ifdef COMPONENT_SYSTEM 
	private ref CF_ViewModel m_ViewModel;
	private ref Managed m_Model;
	#else
	//! In-game, the ref count shouldn't be incremented. When the ref count == 0, then this view should be destroyed.
	private CF_ViewModel m_ViewModel;
	#endif

	//! Lifetimes are managed by the enfusion widgets
	private CF_MVVM_View m_Parent = null;
	private ref set<CF_MVVM_View> m_Children = new set<CF_MVVM_View>();

	private ref array<ref CF_MVVM_Property> m_Properties;
	private map<string, ref CF_MVVM_Property> m_PropertiesMap;

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
		if (CF.MVVM) CF.MVVM._Destroy(m_ViewModel);
		#endif
	}

	void GetProperties(CF_Model_Base model, inout map<string, ref CF_MVVM_Property> properties)
	{
		CF_Trace trace(this, "GetProperties", "" + model, "" + properties);
		
		m_Properties = new array<ref CF_MVVM_Property>();
		m_PropertiesMap = properties;
		GetProperties();

		for (int i = 0; i < m_Properties.Count(); i++)
		{
			m_Properties[i].OnModel(model);
		}

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
		CF_MVVM_Property property = new CF_MVVM_Property(this, "OnView_" + name, "OnModel_" + name);
		m_Properties.Insert(property);
		m_PropertiesMap.Insert(actual, property);
	}
	
	void SetViewModel(CF_ViewModel viewModel)
	{
		CF_Trace trace(this, "SetViewModel", "" + viewModel);

		m_ViewModel = viewModel;
		m_Widget.SetHandler(m_ViewModel);
	}

	void OnView_Children(CF_Model_Base model)
	{
		//@note not within the scope of MVVM.
		// maybe support this at a later stage if possible
	}

	void OnModel_Children(CF_Model_Base model)
	{
		CF_Trace trace(this, "OnModel_Children", "" + model);

		CF_Collection _collection;
		EnScript.GetClassVar(model, Children, 0, _collection);

		int count = _collection.Count();

		for (int i = 0; i < count; i++)
		{
			CF.MVVM.Create(_collection.GetModel(i), _collection.GetLayout(), m_Widget);
		}
	}

	Widget GetWidget()
	{
		return m_Widget;
	}

	set<CF_MVVM_View> GetChildren()
	{
		return m_Children;
	}

	int Count()
	{
		return m_Children.Count();
	}

	CF_MVVM_View Get(int index)
	{
		return m_Children[index];
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
	 * @section	Events
	 * 
	 * @note	Continue is handled in the script widget instead of 'CF_ViewModel' as some 
	 * 			events require reverse cancellation. For example, if 'Continue' is set to 'false'
	 * 			for 'OnChange' in 'CF_EditBoxWidget', then input must be prevented.
	 */
	bool OnClick(CF_MouseEvent evt) { return true; }
	bool OnModalResult(CF_ModalEvent evt) { return true; }
	bool OnDoubleClick(CF_MouseEvent evt) { return true; }
	bool OnSelect(CF_SelectEvent evt) { return true; }
	bool OnItemSelected(CF_ItemSelectEvent evt) { return true; }
	bool OnFocus(CF_PositionEvent evt) { return true; }
	bool OnFocusLost(CF_PositionEvent evt) { return true; }
	bool OnMouseEnter(CF_MouseEvent evt) { return true; }
	bool OnMouseLeave(CF_MouseEvent evt) { return true; }
	bool OnMouseWheel(CF_MouseEvent evt) { return true; }
	bool OnMouseButtonDown(CF_MouseEvent evt) { return true; }
	bool OnMouseButtonUp(CF_MouseEvent evt) { return true; }
	bool OnController(CF_ControllerEvent evt) { return true; }
	bool OnKeyDown(CF_KeyEvent evt) { return true; }
	bool OnKeyUp(CF_KeyEvent evt) { return true; }
	bool OnKeyPress(CF_KeyEvent evt) { return true; }
	bool OnChange(CF_ChangeEvent evt) { return true; }
	bool OnDrag(CF_DragEvent evt) { return true; }
	bool OnDragging(CF_DragEvent evt) { return true; }
	bool OnDraggingOver(CF_DragEvent evt) { return true; }
	bool OnDrop(CF_DragEvent evt) { return true; }
	bool OnDropReceived(CF_DragEvent evt) { return true; }
	bool OnResize(CF_ResizeEvent evt) { return true; }
	bool OnChildAdd(CF_ChildEvent evt) { return true; }
	bool OnChildRemove(CF_ChildEvent evt) { return true; }
	bool OnUpdate(CF_Event evt) { return true; }
};
