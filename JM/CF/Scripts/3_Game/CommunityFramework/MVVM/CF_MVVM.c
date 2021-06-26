class CF_MVVM
{
	private static ref array<ref CF_ViewModel> m_ViewModels;
	private static ref map<CF_ModelBase, CF_ViewModel> m_ViewModelMap;

	private static ref map<typename, ref map<string, ref CF_TypeConverter>> m_PropertyMap;

    #ifdef COMPONENT_SYSTEM
	static bool WB_NEXT_IN_SCRIPT = false;
	#endif

	private void CF_MVVM()
	{

	}

	static CF_MVVM _Init()
	{
		m_ViewModels = new array<ref CF_ViewModel>();
		m_ViewModelMap = new map<CF_ModelBase, CF_ViewModel>();
		
		m_PropertyMap = new map<typename, ref map<string, ref CF_TypeConverter>>();

		CF.Log.Set(CF_LogLevel.ALL);

		return new CF_MVVM();
	}

	static void _Cleanup()
	{
    	#ifndef COMPONENT_SYSTEM
		for (int i = m_ViewModels.Count() - 1; i >= 0; i--)
		{
			_Destroy(m_ViewModels[i]);
		}
		#endif

		m_ViewModels = null;
		m_ViewModelMap = null;
		
		m_PropertyMap = null;
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model
	 */
	static CF_ViewModel Create(CF_ModelBase model, string layout, Widget parent = null)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout, "" + parent);

    	#ifdef COMPONENT_SYSTEM
		if (m_ViewModels == null && m_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (m_ViewModelMap.Find(model, viewModel))
		{
			return viewModel;
		}

    	#ifdef COMPONENT_SYSTEM
		CF.MVVM.WB_NEXT_IN_SCRIPT = true;
		#endif

		viewModel = Create(model, GetGame().GetWorkspace().CreateWidgets(layout, parent));

    	#ifdef COMPONENT_SYSTEM
		CF.MVVM.WB_NEXT_IN_SCRIPT = false;
		#endif

		return viewModel;
	}

	static CF_ViewModel Create(CF_ModelBase model, Widget widget)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + widget);

    	#ifdef COMPONENT_SYSTEM
		if (m_ViewModels == null && m_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (m_ViewModelMap.Find(model, viewModel))
		{
			viewModel._UnlinkView();
		}

		if (!widget) return null;

		CF_MVVM_View view;
		widget.GetScript(view);

		return Create(model, view);
	}

	static CF_ViewModel Create(CF_ModelBase model, CF_MVVM_View view)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + view);

    	#ifdef COMPONENT_SYSTEM
		if (m_ViewModels == null && m_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (m_ViewModelMap.Find(model, viewModel))
		{
			viewModel.SetView(view);
			return viewModel;
		}

		if (!view) return null;

		viewModel = new CF_ViewModel(view, model);
		m_ViewModels.Insert(viewModel);
		m_ViewModelMap.Insert(model, viewModel);
		return viewModel;
	}

	static ref CF_TypeConverter GetPropertyType(CF_ModelBase model, string property)
	{
		CF_Trace trace(CF.MVVM, "GetPropertyType", "" + model, "" + property);

		typename type = model.Type();

		map<string, ref CF_TypeConverter> propertyTypeMap;
		if (!m_PropertyMap.Find(type, propertyTypeMap)) 
		{
			CF.Log.Error("Property wasn't added to property map...");
			return null;
		}
		
		return propertyTypeMap.Get(property);
	}

	static void _LoadPropertyTypes(CF_ModelBase model, CF_MVVM_View view, map<string, ref CF_MVVM_Property> propertyMap, array<ref CF_MVVM_Property> properties)
	{
		CF_Trace trace(CF.MVVM, "_LoadPropertyTypes", "" + model, "" + view, "" + propertyMap);

		map<string, ref CF_TypeConverter> propertyTypeMap;
		typename type = model.Type();
		if (!m_PropertyMap.Find(type, propertyTypeMap))
		{
			propertyTypeMap = new map<string, ref CF_TypeConverter>();
			m_PropertyMap.Insert(type, propertyTypeMap);
		}
		else
		{
		//! Workbench editing
    	#ifdef COMPONENT_SYSTEM
			propertyTypeMap.Clear();
		#else
			for (int j = 0; j < properties.Count(); j++)
			{
				properties[j].Assign(model, view);
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
			if (!propertyMap.Find(variableName, property)) continue;

			property.SetVariableName(variableName);
			property.SetType(variableType);
			
			property.Assign(model, view);

			propertyTypeMap.Insert(variableName, CF.TypeConverters.Create(variableType));
		}
	}

	static void Destroy(CF_ModelBase model)
	{
		CF_Trace trace(CF.MVVM, "Destroy", "" + model);

		CF_ViewModel viewModel;
		if (!m_ViewModelMap.Find(model, viewModel)) return;

		if (!viewModel._DestroyView())
		{
			_Destroy(viewModel);
		}
	}

	static void _Destroy(CF_ViewModel viewModel)
	{
		CF_Trace trace(CF.MVVM, "_Destroy", "" + viewModel);

		m_ViewModelMap.Remove(viewModel.GetModel());
		int idx = m_ViewModels.Find(viewModel);
		if (idx != -1) m_ViewModels.Remove(idx);
	}

	/**
	 * @brief	Fixes issue when script is recompiled while the layout file is opened.
	 * 
	 * @note	To only be using during Workbench editing of layout files.
	 */
    #ifdef COMPONENT_SYSTEM
	static void _Assign(CF_ViewModel viewModel)
	{
		if (m_ViewModels == null && m_ViewModelMap == null)
		{
			CF._GameInit();
		}

		int idx = m_ViewModels.Find(viewModel);
		if (idx == -1)
		{
			m_ViewModels.Insert(viewModel);
		}

		if (!m_ViewModelMap.Contains(viewModel.GetModel()))
		{
			m_ViewModelMap.Insert(viewModel.GetModel(), viewModel);
		}
	}

	static void _CheckInit()
	{
		Print("CHECKING INIT");
		if (m_ViewModels == null && m_ViewModelMap == null)
		{
			Print("NEED INIT");
			CF._GameInit();
		}
	}
	#endif

	static void NotifyPropertyChanged(CF_ModelBase model, string property, CF_Event evt = null)
	{
		CF_Trace trace(CF.MVVM, "NotifyPropertyChanged", "" + model, "" + property);

		CF_ViewModel viewModel;
		if (!m_ViewModelMap.Find(model, viewModel)) return;

		viewModel.NotifyPropertyChanged(property, evt);
	}
};