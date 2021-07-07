class CF_MVVM
{
	private static ref array<ref CF_ViewModel> s_ViewModels;
	private static ref map<CF_ModelBase, CF_ViewModel> s_ViewModelMap;

	private static ref map<typename, ref map<string, ref CF_TypeConverter>> s_PropertyMap;

    #ifdef COMPONENT_SYSTEM
	static bool WB_NEXT_IN_SCRIPT = false;
	#endif

	private void CF_MVVM()
	{

	}

	static CF_MVVM _Init()
	{
		s_ViewModels = new array<ref CF_ViewModel>();
		s_ViewModelMap = new map<CF_ModelBase, CF_ViewModel>();
		
		s_PropertyMap = new map<typename, ref map<string, ref CF_TypeConverter>>();

		CF.Log.Set(0x001111);
		
    	#ifdef COMPONENT_SYSTEM
		CF.Log.Set(CF_LogLevel.ALL);
		#endif

		return new CF_MVVM();
	}

	static void _Cleanup()
	{
    	#ifndef COMPONENT_SYSTEM
		for (int i = s_ViewModels.Count() - 1; i >= 0; i--)
		{
			_Destroy(s_ViewModels[i]);
		}
		#endif

		s_ViewModels = null;
		s_ViewModelMap = null;
		
		s_PropertyMap = null;
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model
	 */
	static CF_ViewModel Create(CF_ModelBase model, string layout)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (s_ViewModelMap.Find(model, viewModel))
		{
			CF_MVVM_View view = viewModel.GetView();
			if (view)
			{
				return viewModel;
			}

			_Destroy(viewModel);
		}

    	#ifdef COMPONENT_SYSTEM
		CF.MVVM.WB_NEXT_IN_SCRIPT = true;
		#endif

		viewModel = Create(model, GetGame().GetWorkspace().CreateWidgets(layout, null));

    	#ifdef COMPONENT_SYSTEM
		CF.MVVM.WB_NEXT_IN_SCRIPT = false;
		#endif

		return viewModel;
	}

	/**
	 * @brief Creates a new View for the model. Returns existing view if it already exists for the model. Updates the parent widget
	 */
	static CF_ViewModel Create(CF_ModelBase model, string layout, Widget parent)
	{
		CF_Trace trace(CF.MVVM, "Create", "" + model, "" + layout, "" + parent);

    	#ifdef COMPONENT_SYSTEM
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (s_ViewModelMap.Find(model, viewModel))
		{
			CF_MVVM_View view = viewModel.GetView();
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

				return viewModel;
			}

			_Destroy(viewModel);
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
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (s_ViewModelMap.Find(model, viewModel))
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
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}
		#endif

		CF_ViewModel viewModel;
		if (s_ViewModelMap.Find(model, viewModel))
		{
			viewModel.SetView(view);
			return viewModel;
		}

		if (!view) return null;

		viewModel = new CF_ViewModel(view, model);
		s_ViewModels.Insert(viewModel);
		s_ViewModelMap.Insert(model, viewModel);
		return viewModel;
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

	static void _LoadPropertyTypes(CF_ModelBase model, CF_MVVM_View view, map<string, ref CF_MVVM_Property> propertyMap, array<ref CF_MVVM_Property> properties)
	{
		CF_Trace trace(CF.MVVM, "_LoadPropertyTypes", "" + model, "" + view, "" + propertyMap);

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
			if (!propertyMap.Find(variableName, property))
			{
				if (!variableType.IsInherited(Widget)) continue;

				property = new CF_MVVM_WidgetProperty(null, variableName);
				propertyMap.Insert(variableName, property);
			}

			property.SetVariableName(variableName);
			property.SetType(variableType);

			// Must be added before Assign
			propertyTypeMap.Insert(variableName, CF.TypeConverters.Create(variableType));
			
			property.Assign(model, view);
		}
	}

	static void Destroy(CF_ModelBase model)
	{
		CF_Trace trace(CF.MVVM, "Destroy", "" + model);

		CF_ViewModel viewModel;
		if (!s_ViewModelMap.Find(model, viewModel)) return;

		if (!viewModel._DestroyView())
		{
			_Destroy(viewModel, false);
		}
	}

	static void _Destroy(CF_ViewModel viewModel, bool forceUI = false)
	{
		CF_Trace trace(CF.MVVM, "_Destroy", "" + viewModel, "" + forceUI);

		if (forceUI && viewModel._DestroyView()) return;

		s_ViewModelMap.Remove(viewModel.GetModel());
		int idx = s_ViewModels.Find(viewModel);
		if (idx != -1) s_ViewModels.Remove(idx);
	}

	/**
	 * @brief	Fixes issue when script is recompiled while the layout file is opened.
	 * 
	 * @note	To only be using during Workbench editing of layout files.
	 */
    #ifdef COMPONENT_SYSTEM
	static void _Assign(CF_ViewModel viewModel)
	{
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}

		int idx = s_ViewModels.Find(viewModel);
		if (idx == -1)
		{
			s_ViewModels.Insert(viewModel);
		}

		if (!s_ViewModelMap.Contains(viewModel.GetModel()))
		{
			s_ViewModelMap.Insert(viewModel.GetModel(), viewModel);
		}
	}

	static void _CheckInit()
	{
		if (s_ViewModels == null && s_ViewModelMap == null)
		{
			CF._GameInit();
		}
	}
	#endif

	static void NotifyPropertyChanged(CF_ModelBase model, string property, CF_EventArgs evt = null)
	{
		CF_Trace trace(CF.MVVM, "NotifyPropertyChanged", "" + model, "" + property);

		CF_ViewModel viewModel;
		if (!s_ViewModelMap.Find(model, viewModel)) return;

		viewModel.NotifyPropertyChanged(property, evt);
	}
};