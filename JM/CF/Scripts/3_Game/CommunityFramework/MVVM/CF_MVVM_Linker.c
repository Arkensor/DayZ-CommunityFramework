typedef array<ref CF_MVVM_Property> CF_TArrayProperties;

class CF_MVVM_Linker
{
	ref CF_EventHandler OnDestroy = new CF_EventHandler();
	
	autoptr CF_Map<string, ref CF_TArrayProperties> m_PropertyVariableMap;
	autoptr CF_TArrayProperties m_Properties;
	CF_ViewModel m_Root;

	void CF_MVVM_Linker()
	{
		m_PropertyVariableMap = new CF_Map<string, ref CF_TArrayProperties>();
		m_Properties = new CF_TArrayProperties();
	}

	void ~CF_MVVM_Linker()
	{
		OnDestroy.Invoke(this);
	}

	/**
	 * @note: To only be called by CF_ViewModel::NotifyPropertyChanged
	 */
	void _ViewChanged(string name, CF_MVVM_Property srcProperty, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_3(this, "_ViewChanged").Add(name).Add(srcProperty).Add(args.GetDebugName());
		#endif

		if (name == string.Empty) return;

		CF_TArrayProperties properties;
		if (!m_PropertyVariableMap.Find(name, properties)) return;

		foreach (auto property : properties)
		{
			if (property == srcProperty) continue;
			property.OnModel(args);
		}
	}

	/**
	 * @note: To only be called by CF_ViewModel::NotifyPropertyChanged
	 */
	void _ViewChanged(CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "_ViewChanged").Add(args.GetDebugName());
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
		auto trace = CF_Trace_2(this, "NotifyPropertyChanged").Add(name).Add(args.GetDebugName());
		#endif

		if (name == string.Empty) return;

		CF_TArrayProperties properties;
		if (!m_PropertyVariableMap.Find(name, properties)) return;

		foreach (auto property : properties)
		{
			property.OnModel(args);
		}
	}

	void NotifyPropertyChanged(CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "NotifyPropertyChanged").Add(args.GetDebugName());
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
		string variableName = property.GetVariableName();
		if (variableName == string.Empty) return;
		
		CF_TArrayProperties properties = m_PropertyVariableMap[variableName];
		if (!properties) properties = new CF_TArrayProperties();
		m_PropertyVariableMap[variableName] = properties;

		properties.Insert(property);
		m_Properties.Insert(property);
	}

	void Link(CF_ViewModel viewModel, CF_ModelBase model)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "Link").Add(viewModel).Add(model);
		#endif

		m_Root = viewModel;
		m_Root._RecursiveSetModel(model, this);

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
			if (!m_PropertyVariableMap.Find(variableName, properties)) continue;
			
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
		m_PropertyVariableMap.Clear();
		m_Properties.Clear();

		if (!m_Root) return;

		m_Root.GetWidget().Unlink();
		m_Root = null;
	}

	bool ChangeParent(Widget newParent)
	{
		if (!m_Root) return false;

		Widget widget = m_Root.GetWidget();
		Widget oldParent = widget.GetParent();

		if (newParent == oldParent) return true;

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
		if (!m_Root) return null;
		return m_Root.GetWidget();
	}
};