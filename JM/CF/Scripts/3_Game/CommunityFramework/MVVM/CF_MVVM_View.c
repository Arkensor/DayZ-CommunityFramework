class CF_MVVM_View
{
	reference bool Debug_Enable;
	reference string Debug_Model;

	private Widget m_LayoutRoot;
	private CF_ViewModel m_ViewModel;

	//! Lifetimes are managed by the enfusion widgets
	private CF_MVVM_View m_Parent = null;
	private ref set<CF_MVVM_View> m_Children = new set<CF_MVVM_View>();

	private ref array<ref CF_MVVM_Property> m_Properties;
	private map<string, ref CF_MVVM_Property> m_PropertiesMap;

	void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		m_LayoutRoot = w;

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

		if (Debug_Enable)
		{
			CF.Game();

			CF.MVVM.Create(Debug_Model.ToType().Spawn(), this);
		}
	}

	void ~CF_MVVM_View()
	{
		CF_Trace trace(this, "~CF_MVVM_View");

		if (CF.MVVM) CF.MVVM._Destroy(m_ViewModel);
	}

	void GetProperties(Class model, inout map<string, ref CF_MVVM_Property> properties)
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
		m_LayoutRoot.SetHandler(m_ViewModel);
	}

	Widget GetLayoutRoot()
	{
		return m_LayoutRoot;
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
};