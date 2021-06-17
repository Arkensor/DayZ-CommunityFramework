class CF_MVVM
{
	private static ref array<ref CF_ViewModel> m_ViewModels;
	private static ref map<CF_Model_Base, CF_ViewModel> m_ViewModelMap;

	private static ref map<typename, ref map<string, CF_MVVM_PropertyType>> m_PropertyMap;

	static void _Init()
	{
		m_ViewModels = new array<ref CF_ViewModel>();
		m_ViewModelMap = new map<CF_Model_Base, CF_ViewModel>();
		m_PropertyMap = new map<typename, ref map<string, CF_MVVM_PropertyType>>();

		CF.Log.Set(CF_LogLevel.ALL);
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

	static CF_ViewModel Create(CF_Model_Base model, string layout, Widget parent = null)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout, "" + parent);

		return Create(model, GetGame().GetWorkspace().CreateWidgets(layout, parent));
	}

	static CF_ViewModel Create(CF_Model_Base model, Widget widget)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + widget);

		if (!widget) return null;

		CF_MVVM_View view;
		widget.GetScript(view);

		return Create(model, view);
	}

	static CF_ViewModel Create(CF_Model_Base model, CF_MVVM_View view)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + view);

		if (!view) return null;

		CF_ViewModel viewModel;
		if (m_ViewModelMap.Find(model, viewModel))
		{
			viewModel.SetView(view);
			return viewModel;
		}

		viewModel = new CF_ViewModel(view, model);
		m_ViewModels.Insert(viewModel);
		m_ViewModelMap.Insert(model, viewModel);
		return viewModel;
	}

	static CF_MVVM_PropertyType GetPropertyType(CF_Model_Base model, string property)
	{
		CF_Trace trace(CF.MVVM, "GetPropertyType", "" + model, "" + property);

		typename type = model.Type();

		map<string, CF_MVVM_PropertyType> propertyTypeMap;
		if (!m_PropertyMap.Find(type, propertyTypeMap)) return CF_MVVM_PropertyType.CLASS;
		
		return propertyTypeMap.Get(property);
	}

	static void _LoadPropertyTypes(CF_Model_Base model, map<string, ref CF_MVVM_Property> propertyMap)
	{
		CF_Trace trace(CF.MVVM, "_LoadPropertyTypes", "" + model, "" + propertyMap);

		map<string, CF_MVVM_PropertyType> propertyTypeMap;
		typename type = model.Type();
		if (!m_PropertyMap.Find(type, propertyTypeMap))
		{
			propertyTypeMap = new map<string, CF_MVVM_PropertyType>();
			m_PropertyMap.Insert(type, propertyTypeMap);
		}
		else
		{
			propertyTypeMap.Clear();
			//return;
		}

		int count = type.GetVariableCount();
		for (int i = 0; i < count; i++)
		{
			string variableName = type.GetVariableName(i);
			typename variableType = type.GetVariableType(i);
			
			CF.Log.Info("%1 %2", variableType.ToString(), variableName);

			if (!propertyMap.Contains(variableName)) continue;

			if (variableType == bool)
			{
				CF.Log.Info("%1 as bool", variableName);
				propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.BOOL);
				continue;
			}

			if (variableType == int)
			{
				CF.Log.Info("%1 as int", variableName);
				propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.INT);
				continue;
			}
			
			if (variableType == float)
			{
				CF.Log.Info("%1 as float", variableName);
				propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.FLOAT);
				continue;
			}
			
			if (variableType == string)
			{
				CF.Log.Info("%1 as string", variableName);
				propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.STRING);
				continue;
			}
			
			if (variableType == vector)
			{
				CF.Log.Info("%1 as vector", variableName);
				propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.VECTOR);
				continue;
			}
			
			CF.Log.Info("%1 as Class", variableName);
			propertyTypeMap.Insert(variableName, CF_MVVM_PropertyType.CLASS);
		}
	}

	static void Destroy(CF_Model_Base model)
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
	#endif

	static void NotifyPropertyChanged(CF_Model_Base model, string property)
	{
		CF_Trace trace(CF.MVVM, "NotifyPropertyChanged", "" + model, "" + property);

		CF_ViewModel viewModel;
		if (!m_ViewModelMap.Find(model, viewModel)) return;

		viewModel.NotifyPropertyChanged(property);
	}
};