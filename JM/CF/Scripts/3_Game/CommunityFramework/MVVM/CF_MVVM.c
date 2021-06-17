class CF_MVVM
{
	private static ref array<ref CF_ViewModel> m_ViewModels;
	private static ref map<CF_Model_Base, CF_ViewModel> m_ViewModelMap;

	static void _Init()
	{
		m_ViewModels = new array<ref CF_ViewModel>();
		m_ViewModelMap = new map<CF_Model_Base, CF_ViewModel>();

		CF.Log.Set(CF_LogLevel.ALL);
	}

	static void _Cleanup()
	{
		for (int i = m_ViewModels.Count() - 1; i >= 0; i--)
		{
			_Destroy(m_ViewModels[i]);
		}

		m_ViewModels = null;
		m_ViewModelMap = null;
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