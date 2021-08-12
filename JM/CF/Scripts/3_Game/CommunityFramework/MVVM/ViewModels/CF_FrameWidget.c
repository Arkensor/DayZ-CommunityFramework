class CF_FrameWidget : CF_Widget
{
	reference string SubModel;
	reference string SubLayoutOverride;

	protected ref CF_ModelBase _SubModel;

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();

		AddProperty(SubModel, "SubModel");
	}

	void OnView_SubModel(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_SubModel", "" + sender, args.ToStr());
		#endif
		
		// Never called.
	}

	void OnModel_SubModel(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_SubModel", "" + sender, args.ToStr());
		#endif
		
		CF_ModelBase _model;
		EnScript.GetClassVar(m_Model, SubModel, 0, _model);

		if (_SubModel == _model) return;

		_SubModel = _model;

		if (_SubModel != null)
		{
			string layoutPath = SubLayoutOverride;
			if (layoutPath == string.Empty)
			{
				g_Script.CallFunction(_SubModel, "GetLayoutFile", layoutPath, null);
			}

			CF_MVVM.Create(_SubModel, layoutPath, _Widget);
		}
		else if (_SubModel)
		{
			CF_MVVM.Destroy(_SubModel);
		}
	}
};
