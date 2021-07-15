typedef CF_Map<string, CF_MVVM_Property> CF_MVVM_Properties;

class CF_MVVM_Link
{
	ref CF_MVVM_Properties m_Properties = new CF_MVVM_Properties();
	CF_MVVM_View m_View;
};

class CF_MVVM
{
	private static ref map<CF_ModelBase, ref CF_MVVM_Link> s_ViewModelMap;

	private static ref map<typename, ref map<string, ref CF_TypeConverter>> s_PropertyMap;

    #ifdef COMPONENT_SYSTEM
	static bool WB_NEXT_IN_SCRIPT = false;
	#endif

	private void CF_MVVM()
	{

	}

	static CF_MVVM _Init()
	{
		s_ViewModelMap = new map<CF_ModelBase, ref CF_MVVM_Link>();
		
		s_PropertyMap = new map<typename, ref map<string, ref CF_TypeConverter>>();

		CF.Log.Set(0x001111);
		
    	#ifdef COMPONENT_SYSTEM
		CF.Log.Set(CF_LogLevel.ALL);
		#endif

		return new CF_MVVM();
	}

	static void _Cleanup()
	{
		s_ViewModelMap = null;
		
		s_PropertyMap = null;
	}

	static CF_MVVM_Link _GetLink(CF_ModelBase model)
	{
		CF_Trace trace(CF.MVVM, "_GetLink", "" + model);

		return s_ViewModelMap[model];
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model
	 */
	static void Create(CF_ModelBase model, string layout)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (s_ViewModelMap.Find(model, link))
		{
			if (link.m_View) return;

			Destroy(model);
		}

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = true;
		#endif

		Widget widget = GetGame().GetWorkspace().CreateWidgets(layout, null);

		Connect(model, widget);

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = false;
		#endif
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model. Updates the parent widget
	 */
	static void Create(CF_ModelBase model, string layout, Widget parent)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout, "" + parent);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (s_ViewModelMap.Find(model, link))
		{
			CF_MVVM_View view = link.m_View;
			if (view)
			{
				Widget widget = view.GetWidget();
				Widget old_parent = widget.GetParent();

				if (old_parent && old_parent != parent)
				{
					old_parent.RemoveChild(widget);
				}

				if (parent && old_parent != parent)
				{
					parent.AddChild(widget);
				}

				return;
			}

			Destroy(model);
		}

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = true;
		#endif

		Connect(model, GetGame().GetWorkspace().CreateWidgets(layout, parent));

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = false;
		#endif
	}

	static void Connect(CF_ModelBase model, Widget widget)
	{
		CF_Trace trace(CF.MVVM, "Connect", "" + model, "" + widget);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (s_ViewModelMap.Find(model, link))
		{
			if (!link.m_View) return;

			link.m_View.GetWidget().Unlink();
			link.m_View = null;
		}

		if (!widget) return;

		CF_MVVM_View view;
		widget.GetScript(view);

		Connect(model, view);
	}

	static void Connect(CF_ModelBase model, notnull CF_MVVM_View view)
	{
		CF_Trace trace(CF.MVVM, "Connect", "" + model, "" + view);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		view.SetModel(model);

		CF_MVVM_Link link;
		if (s_ViewModelMap.Find(model, link))
		{
			link.m_View = view;
			return;
		}

		link = new CF_MVVM_Link();
		link.m_View = view;
		s_ViewModelMap.Insert(model, link);
	}

	static ref CF_TypeConverter GetPropertyType(CF_ModelBase model, string property)
	{
		CF_Trace trace(CF.MVVM, "GetPropertyType", "" + model, "" + property);

		typename type = model.Type();

		map<string, ref CF_TypeConverter> propertyTypeMap;
		if (!s_PropertyMap.Find(type, propertyTypeMap)) 
		{
			CF.Log.Error("Property wasn't added to property map...");
			return null;
		}
		
		return propertyTypeMap.Get(property);
	}

	static void _LoadPropertyTypes(CF_ModelBase model, CF_MVVM_View view, CF_Map<string, ref CF_MVVM_Property> properties)
	{
		CF_Trace trace(CF.MVVM, "_LoadPropertyTypes", "" + model, "" + view, "" + properties);

		map<string, ref CF_TypeConverter> propertyTypeMap;
		typename type = model.Type();
		if (!s_PropertyMap.Find(type, propertyTypeMap))
		{
			propertyTypeMap = new map<string, ref CF_TypeConverter>();
			s_PropertyMap.Insert(type, propertyTypeMap);
		}
		else
		{
		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
			propertyTypeMap.Clear();
		#else
			for (int j = 0; j < properties.Count(); j++)
			{
				properties.GetElement(j).Assign(model, view);
			}

			return;
		#endif
		}

		int count = type.GetVariableCount();
		for (int i = 0; i < count; i++)
		{
			string variableName = type.GetVariableName(i);
			typename variableType = type.GetVariableType(i);

			CF_MVVM_Property property;
			if (!properties.Find(variableName, property))
			{
				if (!variableType.IsInherited(Widget)) continue;

				property = new CF_MVVM_WidgetProperty(null, variableName);
				properties.Insert(variableName, property);
			}

			property.SetVariableName(variableName);
			property.SetType(variableType);

			// Must be added before Assign
			propertyTypeMap.Insert(variableName, CF.TypeConverters.Create(variableType));
			
			property.Link(model);
		}
	}

	static void Destroy(CF_ModelBase model)
	{
		CF_Trace trace(CF.MVVM, "Destroy", "" + model);

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		link.m_View.GetWidget().Unlink();

		s_ViewModelMap.Remove(model);
	}

	/**
	 * @brief	Fixes issue when script is recompiled while the layout file is opened.
	 * 
	 * @note	To only be using during Workbench editing of layout files.
	 */
    #ifdef COMPONENT_SYSTEM
	static void _CheckInit()
	{
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
	}
	#endif

	static void NotifyPropertyChanged(CF_ModelBase model, string propertyName, CF_EventArgs evt = null)
	{
		CF_EventArgs temp = evt;
		if (temp == null) temp = new CF_EventArgs();

		CF_Trace trace(CF.MVVM, "NotifyPropertyChanged", "" + model, "" + propertyName, temp.String());

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		CF_MVVM_Property property;
		if (!properties.Find(propertyName, property)) return;

		property.OnModel(temp);
	}

	static void NotifyPropertyChanged(CF_ModelBase model)
	{
		CF_EventArgs temp = new CF_EventArgs();

		CF_Trace trace(CF.MVVM, "NotifyPropertyChanged", "" + model);

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		int count = properties.Count();
		for (int i = 0; i < count; i++)
		{
			properties.GetElement(i).OnModel(temp);
		}
	}

	void AddProperty(CF_ModelBase model, CF_MVVM_Property property)
	{
		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link))
		{
			link = new CF_MVVM_Link();
			s_ViewModelMap.Insert(model, link);
		}

		CF_MVVM_Properties properties = link.m_Properties;
		
		properties.Insert(property.GetVariableName(), property);
	}

	void RemoveProperty(CF_ModelBase model, string propertyName)
	{
		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		properties.Remove(propertyName);
	
		if (properties.Count() == 0)
		{
			Destroy(model);
		}
	}
};