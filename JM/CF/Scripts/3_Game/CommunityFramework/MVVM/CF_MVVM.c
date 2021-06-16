class CF_MVVM
{
	private ref array<ref CF_ViewModel> m_ViewModels = new array<ref CF_ViewModel>();
	private ref map<Class, CF_ViewModel> m_ViewModelMap = new map<Class, CF_ViewModel>();

	CF_ViewModel Create(Class model, string layout, Widget parent = null)
	{
		CF_Trace trace(this, "Create", "" + model, "" + layout, "" + parent);

		return Create(model, GetGame().GetWorkspace().CreateWidgets(layout, parent));
	}

	CF_ViewModel Create(Class model, Widget widget)
	{
		CF_Trace trace(this, "Create", "" + model, "" + widget);

		if (!widget) return null;

		CF_MVVM_View view;
		widget.GetScript(view);

		return Create(model, view);
	}

	CF_ViewModel Create(Class model, CF_MVVM_View view)
	{
		CF_Trace trace(this, "Create", "" + model, "" + view);

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

	void Destroy(Class model)
	{
		CF_Trace trace(this, "Destroy", "" + model);

		CF_ViewModel viewModel;
		if (!m_ViewModelMap.Find(model, viewModel)) return;

		if (!viewModel._DestroyView())
		{
			_Destroy(viewModel);
		}
	}

	void _Destroy(CF_ViewModel viewModel)
	{
		CF_Trace trace(this, "_Destroy", "" + viewModel);

		m_ViewModelMap.Remove(viewModel.GetModel());
		int idx = m_ViewModels.Find(viewModel);
		if (idx != -1) m_ViewModels.Remove(idx);
	}

	void NotifyPropertyChanged(Class model, string property)
	{
		CF_Trace trace(this, "NotifyPropertyChanged", "" + model, "" + property);

		CF_ViewModel viewModel;
		if (!m_ViewModelMap.Find(model, viewModel)) return;

		viewModel.NotifyPropertyChanged(property);
	}
};