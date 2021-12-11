typedef array<ref CF_MVVM_Property> CF_TArrayProperties;

class CF_MVVM_Linker
{
	ref CF_EventHandler OnDestroy = new CF_EventHandler();

	autoptr CF_Map<string, ref CF_TArrayProperties> m_PropertyVariableMap;
	autoptr CF_TArrayProperties m_Properties;
	CF_ViewModel m_Root;

	CF_MVVM_Linker m_Parent;
	autoptr array<CF_MVVM_Linker> m_Children = new array<CF_MVVM_Linker>();

	int m_DestroyLockCount;
	bool m_IsBeingDestroyed;

	void CF_MVVM_Linker()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_MVVM_Linker");
#endif

		m_PropertyVariableMap = new CF_Map<string, ref CF_TArrayProperties>();
		m_Properties = new CF_TArrayProperties();
	}

	void ~CF_MVVM_Linker()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_MVVM_Linker");
#endif

		if (m_Parent)
		{
			m_Parent.RemoveChild(this);
		}

		OnDestroy.Invoke(this);
	}

	/**
	 * @note: To only be called by CF_ViewModel::NotifyPropertyChanged
	 */
	void _ViewChanged(string name, CF_MVVM_Property srcProperty, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3(this, "_ViewChanged").Add(name).Add(srcProperty).Add(args);
#endif

		if (name == string.Empty)
			return;

		CF_TArrayProperties properties;
		if (!m_PropertyVariableMap.Find(name, properties))
			return;

		foreach (auto property : properties)
		{
			if (property == srcProperty)
				continue;
			property.OnModel(args);
		}
	}

	/**
	 * @note: To only be called by CF_ViewModel::NotifyPropertyChanged
	 */
	void _ViewChanged(CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "_ViewChanged").Add(args);
#endif

		for (int j = 0; j < m_PropertyVariableMap.Count(); j++)
		{
			CF_TArrayProperties properties = m_PropertyVariableMap.GetElement(j);

			foreach (auto property : properties)
			{
				property.OnView(args);
			}
		}
	}

	void NotifyPropertyChanged(string name, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "NotifyPropertyChanged").Add(name).Add(args);
#endif

		if (name == string.Empty)
			return;

		CF_TArrayProperties properties;
		if (!m_PropertyVariableMap.Find(name, properties))
			return;

		foreach (auto property : properties)
		{
			property.OnModel(args);
		}
	}

	void NotifyPropertyChanged(CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "NotifyPropertyChanged").Add(args);
#endif

		for (int j = 0; j < m_PropertyVariableMap.Count(); j++)
		{
			CF_TArrayProperties properties = m_PropertyVariableMap.GetElement(j);

			foreach (auto property : properties)
			{
				property.OnModel(args);
			}
		}
	}

	void Insert(CF_MVVM_Property property)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Insert").Add(property);
#endif

		string variableName = property.GetVariableName();
		if (variableName == string.Empty)
			return;

		CF_TArrayProperties properties = m_PropertyVariableMap[variableName];
		if (!properties)
			properties = new CF_TArrayProperties();
		m_PropertyVariableMap[variableName] = properties;

		properties.Insert(property);
		m_Properties.Insert(property);
	}

	void Relink()
	{
		m_Root._SetRootLink(this);
	}

	void Link(CF_ViewModel viewModel, CF_ModelBase model)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Link").Add(viewModel).Add(model);
#endif

		m_Root = viewModel;
		m_Root._RecursiveSetModel(model, this);
		m_Root._SetRootLink(this);

		typename modelType = model.Type();
		int count = modelType.GetVariableCount();
		for (int i = 0; i < count; i++)
		{
			string variableName = modelType.GetVariableName(i);
			typename variableType = modelType.GetVariableType(i);

			if (variableType.IsInherited(Widget))
			{
				Insert(new CF_MVVM_WidgetProperty(viewModel, variableName));
			}

			CF_TArrayProperties properties;
			if (!m_PropertyVariableMap.Find(variableName, properties))
				continue;

			auto typeConverter = CF_TypeConverter.Get(variableType);

			foreach (auto property : properties)
			{
				property.Link(model, variableType, typeConverter);
			}
		}
	}

	bool IsValid()
	{
		return m_Root != null;
	}

	void Unlink()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Unlink");
#endif

		m_IsBeingDestroyed = true;

		if (_IsLockedForDestroy())
		{
			return;
		}

		_Destroy();
	}

	void _Destroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "_Destroy");
#endif

		m_PropertyVariableMap.Clear();
		m_Properties.Clear();

		if (!m_Root)
		{
			return;
		}

		if (m_Root.GetWidget())
		{
			m_Root.GetWidget().Unlink();
		}

		m_Root = null;
	}

	bool ChangeParent(Widget newParent)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "ChangeParent").Add(newParent);
#endif

		if (!m_Root)
			return false;

		Widget widget = m_Root.GetWidget();
		Widget oldParent = widget.GetParent();

		if (newParent == oldParent)
			return true;

		OnDestroy.Invoke(this);

		if (oldParent && oldParent != newParent)
		{
			oldParent.RemoveChild(widget);
		}

		if (newParent && oldParent != newParent)
		{
			newParent.AddChild(widget);
		}

		return true;
	}

	Widget GetWidget()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetWidget");
#endif

		if (!m_Root)
		{
			return null;
		}
		
		return m_Root.GetWidget();
	}

	bool _IsLockedForDestroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "_IsLockedForDestroy");
#endif

		foreach (auto child : m_Children)
		{
			if (child._IsLockedForDestroy())
			{
				return true;
			}
		}

		return m_DestroyLockCount > 0;
	}

	void _LockForDestroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "_LockForDestroy");
#endif

		m_DestroyLockCount++;
	}

	void _UnlockForDestroy()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "_UnlockForDestroy");
#endif

		m_DestroyLockCount--;

		if (m_DestroyLockCount < 0)
		{
			string className = "null";
			string debugName = "";
			if (m_Root.GetModel())
			{
				className = m_Root.GetModel().ClassName();
				debugName = m_Root.GetModel().GetDebugName();
			}

			CF_Log.Warn("Destroy lock count reached below zero for %1 \"%2\"", className, debugName);

			m_DestroyLockCount = 0;
		}
		else if (!m_DestroyLockCount && m_IsBeingDestroyed)
		{
			_Destroy();
		}
	}

	void AddChild(CF_MVVM_Linker child)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "AddChild").Add(child);
#endif

		if (child.m_Parent)
			child.m_Parent.RemoveChild(child);

		m_Children.Insert(child);
		child.m_Parent = this;
	}

	void RemoveChild(CF_MVVM_Linker child)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "RemoveChild").Add(child);
#endif

		if (child.m_Parent != this)
		{
			return;
		}

		for (int i = 0; i < m_Children.Count(); i++)
		{
			if (m_Children[i] == child)
			{
				child.m_Parent = null;
				m_Children.Remove(i);
				return;
			}
		}
	}
};
