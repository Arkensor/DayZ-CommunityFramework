class CF_FrameWidget : CF_Widget
{
	reference string SubModel;
	reference string SubModelType;
	reference string SubLayoutOverride;

	reference string SubModelProperty0;
	reference string SubModelProperty1;

	protected ref array<CF_MVVM_SubProperty> _SubProperties = new array<CF_MVVM_SubProperty>();
	protected ref CF_ModelBase _SubModel;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

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
		CF_MVVM.AddSourceProperty(m_Properties, actual, name, property);
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);

		if (SubModel == string.Empty && SubModelType != string.Empty)
		{
			if (!Class.CastTo(_SubModel, SubModelType.ToType().Spawn()))
			{
				CF_Log.Error("Error creating sub m_Model %1", SubModelType);
				return;
			}

			if (SubLayoutOverride == string.Empty)
			{
				g_Script.CallFunction(_SubModel, "GetLayout", SubLayoutOverride, null);
			}

			CF_MVVM.Create(_SubModel, SubLayoutOverride, _Widget);
		}
	}

	void OnUpdateSubViewModel()
	{
		CF_Trace trace(this, "OnUpdateSubViewModel");

		if (!_SubModel) return;
		
		for (int i = 0; i < _SubProperties.Count(); i++)
		{
			_SubProperties[i].SetSubModel(_SubModel);
		}
	}

	void OnView_SubModel(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_SubModel", "" + sender, args.ToStr());
		
		// Never called.
	}

	void OnModel_SubModel(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_SubModel", "" + sender, args.ToStr());
		
		CF_ModelBase _model;
		EnScript.GetClassVar(m_Model, SubModel, 0, _model);

		if (_SubModel == _model) return;

		_SubModel = _model;

		if (_SubModel != null)
		{
			string layoutPath = SubLayoutOverride;
			if (layoutPath == string.Empty)
			{
				g_Script.CallFunction(_SubModel, "GetLayout", layoutPath, null);
			}

			CF_MVVM.Create(_SubModel, layoutPath, _Widget);
		}
		else if (_SubModel)
		{
			CF_MVVM.Destroy(_SubModel);
		}

		OnUpdateSubViewModel();
	}
};
