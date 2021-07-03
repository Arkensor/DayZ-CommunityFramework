class CF_FrameWidget : CF_Widget
{
	reference string SubModel;
	reference string SubModelType;
	reference string SubLayoutOverride;

	reference string SubModelProperty0;
	reference string SubModelProperty1;

	protected CF_ViewModel _SubViewModel;
	protected ref array<CF_MVVM_SubProperty> _SubProperties = new array<CF_MVVM_SubProperty>();

	override void GetProperties()
	{
		super.GetProperties();

		AddProperty(SubModel, "SubModel");

		AddSubProperty(SubModelProperty0, "SubModelProperty0");
		AddSubProperty(SubModelProperty1, "SubModelProperty1");

		OnUpdateSubViewModel();
	}

	protected void AddSubProperty(string actual, string name)
	{
		CF_Trace trace(this, "AddSubProperty", "Actual=" + actual + " Name=" + name);
		
		if (actual == string.Empty) return;
		CF_MVVM_SubProperty property = new CF_MVVM_SubProperty(this, name);
		_SubProperties.Insert(property);
		m_Properties.Insert(property);
		m_PropertiesMap.Insert(actual, property);
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);

		if (SubModel == string.Empty && SubModelType != string.Empty)
		{
			CF_ModelBase model;
			if (!Class.CastTo(model, SubModelType.ToType().Spawn()))
			{
				CF.Log.Error("Error creating sub model %1", SubModelType);
				return;
			}

			if (SubLayoutOverride == string.Empty)
			{
				g_Script.CallFunction(model, "GetLayout", SubLayoutOverride, null);
			}

			_SubViewModel = CF.MVVM.Create(model, SubLayoutOverride, _Widget);
		}
	}

	void OnUpdateSubViewModel()
	{
		CF_ModelBase subModel;

		if (_SubViewModel)
		{
			subModel = _SubViewModel.GetModel();
		}

		for (int i = 0; i < _SubProperties.Count(); i++)
		{
			_SubProperties[i].SetSubModel(subModel);
		}
	}

	void OnView_SubModel(CF_ModelBase model, CF_EventArgs evt)
	{
		// Never called.
	}

	void OnModel_SubModel(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_ModelBase _model;
		EnScript.GetClassVar(model, SubModel, 0, _model);

		if (_SubViewModel && _SubViewModel.GetModel() == _model) return;

		if (_model != null)
		{
			if (SubLayoutOverride == string.Empty)
			{
				g_Script.CallFunction(model, "GetLayout", SubLayoutOverride, null);
			}

			_SubViewModel = CF.MVVM.Create(model, SubLayoutOverride, _Widget);
		}
		else
		{
			CF.MVVM._Destroy(_SubViewModel);
		}

		OnUpdateSubViewModel();
	}
};
