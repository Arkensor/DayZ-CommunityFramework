//TODO: massive cleanup of CF_MVVM_Properties, CF_MVVM_SourceProperties and CF_MVVM_Link
typedef CF_Map<string, ref array<ref CF_MVVM_Property>> CF_MVVM_Properties;
typedef CF_Map<string, ref CF_Map<string, ref CF_MVVM_Property>> CF_MVVM_SourceProperties;

class CF_MVVM_Link
{
	ref CF_MVVM_Properties m_Properties = new CF_MVVM_Properties();
	CF_ViewModel m_View;
};

static autoptr CF_MVVM g_CF_MVVM = null;

class CF_MVVM
{
	private static ref map<CF_ModelBase, ref CF_MVVM_Link> s_ViewModelMap;

	private static ref map<typename, ref map<string, ref CF_TypeConverter>> s_PropertyMap;

    #ifdef COMPONENT_SYSTEM
	static bool WB_NEXT_IN_SCRIPT = false;
	#endif

	private void CF_MVVM()
	{
		CF_Trace trace(this, "CF_MVVM");
	}

	[CF_EventSubscriber(CF_MVVM._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		if (g_CF_MVVM) return;

		s_ViewModelMap = new map<CF_ModelBase, ref CF_MVVM_Link>();
		
		s_PropertyMap = new map<typename, ref map<string, ref CF_TypeConverter>>();

		CF_Log.Set(0x001111);
		
    	#ifdef COMPONENT_SYSTEM
		CF_Log.Set(CF_LogLevel.ALL);
		#endif

		g_CF_MVVM = new CF_MVVM();
	}

	[CF_EventSubscriber(CF_Windows._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		s_ViewModelMap = null;
		
		s_PropertyMap = null;

		g_CF_MVVM = null;
	}

	static CF_MVVM_Link _GetLink(CF_ModelBase model)
	{
		CF_Trace trace(g_CF_MVVM, "_GetLink", "" + model);

		return s_ViewModelMap[model];
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model
	 */
	static void Create(CF_ModelBase model, string layout)
	{
		CF_Trace trace(g_CF_MVVM, "Create", "" + model, "" + layout);

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
		CF_Trace trace(g_CF_MVVM, "Create", "" + model, "" + layout, "" + parent);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (s_ViewModelMap.Find(model, link))
		{
			CF_ViewModel view = link.m_View;
			if (view)
			{
				Widget widget = view.GetWidget();
				Widget old_parent = widget.GetParent();

				if (parent == old_parent) return;

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

		WorkspaceWidget wSpace = GetGame().GetWorkspace();
		// A mess to fix an issue in Workbench, can also substitute for loading screen support
		if (wSpace == null)
		{
			wSpace = GetGame().GetLoadingWorkspace();
			if (!wSpace) wSpace = CF.Game().GetWorkspace();
			if (!wSpace) wSpace = CF.Game().GetLoadingWorkspace();

			if (!wSpace) return;
		}

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = true;
		#endif

		Connect(model, wSpace.CreateWidgets(layout, parent));

    	#ifdef COMPONENT_SYSTEM
		CF_MVVM.WB_NEXT_IN_SCRIPT = false;
		#endif
	}

	static void Connect(CF_ModelBase model, Widget widget)
	{
		CF_Trace trace(g_CF_MVVM, "Connect", "" + model, "" + widget);

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

		CF_ViewModel view;
		widget.GetScript(view);

		Connect(model, view);
	}

	static void Connect(CF_ModelBase model, notnull CF_ViewModel view)
	{
		CF_Trace trace(g_CF_MVVM, "Connect", "" + model, "" + view);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link))
		{
			link = new CF_MVVM_Link();
			s_ViewModelMap.Insert(model, link);
		}

		link.m_View = view;
		link.m_View.SetModel(model);
	}

	static ref CF_TypeConverter GetPropertyType(CF_ModelBase model, string property)
	{
		CF_Trace trace(g_CF_MVVM, "GetPropertyType", "" + model, "" + property);

		typename type = model.Type();

		map<string, ref CF_TypeConverter> propertyTypeMap;
		if (!s_PropertyMap.Find(type, propertyTypeMap)) 
		{
			CF_Log.Error("Property wasn't added to property map...");
			return null;
		}
		
		return propertyTypeMap.Get(property);
	}

	static void _LoadPropertyTypes(CF_ModelBase model, CF_ViewModel view, CF_MVVM_Properties properties)
	{
		CF_Trace trace(g_CF_MVVM, "_LoadPropertyTypes", "" + model, "" + view, properties.ToStr());

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;
		
		array<ref CF_MVVM_Property> propertyList;
		CF_MVVM_Property property;
		CF_MVVM_Properties mapTo = link.m_Properties;
		
		mapTo.Clear();
		
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
				property = properties.GetElement(j);
				mapTo.Insert(properties.GetKey(j), property);
				property.Link(model);
			}

			return;
		#endif
		}

		int count = type.GetVariableCount();
		for (int i = 0; i < count; i++)
		{
			string variableName = type.GetVariableName(i);
			typename variableType = type.GetVariableType(i);

			if (variableType.IsInherited(Widget))
			{
				AddProperty(properties, variableName, new CF_MVVM_WidgetProperty(null, variableName));
			}

			if (!properties.Find(variableName, propertyList)) continue;
			
			// Must be inserted before Link
			propertyTypeMap.Insert(variableName, CF_TypeConverters.Create(variableType));

			for (int k = 0; k < propertyList.Count(); k++)
			{
				property = propertyList[k];
				property.SetType(variableType);
				
				property.Link(model);
				
				CF_MVVM.AddProperty(mapTo, variableName, property);
			}
		}
	}

	static void Destroy(CF_ModelBase model)
	{
		CF_Trace trace(g_CF_MVVM, "Destroy", "" + model);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

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

		CF_Trace trace(g_CF_MVVM, "NotifyPropertyChanged", "" + model, "" + propertyName, temp.ToStr());
		
    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		array<ref CF_MVVM_Property> propertyList;
		if (!properties.Find(propertyName, propertyList)) return;

		foreach (auto property : propertyList) property.OnModel(temp);
	}

	static void NotifyPropertyChanged(CF_ModelBase model)
	{
		CF_EventArgs temp = new CF_EventArgs();

		CF_Trace trace(g_CF_MVVM, "NotifyPropertyChanged", "" + model);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		int count = properties.Count();
		for (int i = 0; i < count; i++)
		{
			foreach (auto property : properties.GetElement(i))
			{
				property.OnModel(temp);
			}
		}
	}

	void AddProperty(CF_ModelBase model, CF_MVVM_Property property)
	{
		CF_Trace trace(g_CF_MVVM, "AddProperty", "" + model, "" + property);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link))
		{
			link = new CF_MVVM_Link();
			s_ViewModelMap.Insert(model, link);
		}

		CF_MVVM.AddProperty(link.m_Properties, property.GetVariableName(), property);
	}

	void RemoveProperty(CF_ModelBase model, string propertyName)
	{
		CF_Trace trace(g_CF_MVVM, "RemoveProperty", "" + model, "" + propertyName);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_MVVM_Link link;
		if (!s_ViewModelMap.Find(model, link)) return;

		CF_MVVM_Properties properties = link.m_Properties;

		properties.Remove(propertyName);
	
		if (properties.Count() == 0)
		{
			Destroy(model);
		}
	}

	static void AddProperty(inout CF_MVVM_Properties propertiesMap, string variableName, CF_MVVM_Property property)
	{
		if (variableName == string.Empty) return;
		
		array<ref CF_MVVM_Property> properties = propertiesMap[variableName];
		if (!properties) properties = new array<ref CF_MVVM_Property>();
		propertiesMap[variableName] = properties;
		properties.Insert(property);
	}

	static void AddSourceProperty(inout CF_MVVM_SourceProperties propertiesMap, string variableName, string sourceName, CF_MVVM_Property property)
	{
		if (variableName == string.Empty || sourceName == string.Empty) return;
		
		CF_Map<string, ref CF_MVVM_Property> properties = propertiesMap[variableName];
		if (!properties) properties = new CF_Map<string, ref CF_MVVM_Property>;
		propertiesMap[variableName] = properties;
		properties.Insert(sourceName, property);
	}
};