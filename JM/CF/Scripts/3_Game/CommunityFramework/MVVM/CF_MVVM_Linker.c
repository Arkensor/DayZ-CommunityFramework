typedef array<ref CF_MVVM_Property> CF_TArrayProperties;

class CF_MVVM_Linker
{
	autoptr CF_Map<string, ref CF_TArrayProperties> m_PropertyVariableMap;
	autoptr CF_TArrayProperties m_Properties;
	CF_ViewModel m_Root;

	void CF_MVVM_Linker()
	{
		m_PropertyVariableMap = new CF_Map<string, ref CF_TArrayProperties>();
		m_Properties = new CF_TArrayProperties();
	}

	/**
	 * @note: To only be called by CF_ViewModel::NotifyPropertyChanged
	 */
	void _ViewChanged(string name, CF_MVVM_Property srcProperty, CF_EventArgs args)
	{
		CF_Trace trace(this, "_ViewChanged", "" + name, "" + srcProperty, args.ToStr());

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
		CF_Trace trace(this, "_ViewChanged", args.ToStr());

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
		CF_Trace trace(this, "NotifyPropertyChanged", "" + name, args.ToStr());

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
		CF_Trace trace(this, "NotifyPropertyChanged", args.ToStr());

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
		CF_Trace trace(this, "Link", "" + viewModel, "" + model);

		m_Root = viewModel;
		m_Root._RecursiveSetModel(model, this);

		typename modelType = model.Type();
						
		map<string, ref CF_TypeConverter> propertyTypeMap;
		if (!CF_MVVM.s_PropertyMap.Find(modelType, propertyTypeMap))
		{
			propertyTypeMap = new map<string, ref CF_TypeConverter>();
			CF_MVVM.s_PropertyMap.Insert(modelType, propertyTypeMap);
		}
		else
		{
		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
			propertyTypeMap.Clear();
		#else
			for (int j = 0; j < m_Properties.Count(); j++)
			{
				m_Properties[j].Link(model);
			}

			return;
		#endif
		}

		int count = modelType.GetVariableCount();
		for (int i = 0; i < count; i++)
		{
			string variableName = modelType.GetVariableName(i);
			typename variableType = modelType.GetVariableType(i);

			if (variableType.IsInherited(Widget))
			{
				Insert(new CF_MVVM_WidgetProperty(null, variableName));
			}

			CF_TArrayProperties properties;
			if (!m_PropertyVariableMap.Find(variableName, properties)) continue;
			
			// Must be inserted before Link
			propertyTypeMap.Insert(variableName, CF_TypeConverters.Create(variableType));

			foreach (auto property : properties)
			{
				property.SetType(variableType);
				property.Link(model);
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
