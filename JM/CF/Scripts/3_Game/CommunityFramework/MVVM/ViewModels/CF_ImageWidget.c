class CF_ImageWidget : CF_Widget
{
	reference string Index;
	reference string File;
	reference string MaskFile;
	reference string MaskProgress;
	reference string MaskTransitionWidth;

	protected ImageWidget _ImageWidget;
	protected CF_MVVM_PropertyBase _Index = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _File = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _MaskFile = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _MaskProgress = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _MaskTransitionWidth = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(Index, "Index");
		AddProperty(File, "File");
		AddProperty(MaskFile, "MaskFile");
		AddProperty(MaskProgress, "MaskProgress");
		AddProperty(MaskTransitionWidth, "MaskTransitionWidth");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ImageWidget, w);
	}

	void OnView_Index(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Index", "" + sender, args.ToStr());
		#endif
		
		_Index.SetInt(_ImageWidget.GetImage());
	}

	void OnModel_Index(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Index", "" + sender, args.ToStr());
		#endif
		
		_ImageWidget.SetImage(_Index.GetInt());
	}

	void OnView_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_File", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_File", "" + sender, args.ToStr());
		#endif
		
		_ImageWidget.LoadImageFile(_Index.GetInt(), _File.GetString());
	}

	void OnView_MaskFile(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_MaskFile", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_MaskFile(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_MaskFile", "" + sender, args.ToStr());
		#endif
		
		_ImageWidget.LoadMaskTexture(_MaskFile.GetString());
	}

	void OnView_MaskProgress(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_MaskProgress", "" + sender, args.ToStr());
		#endif
		
		_MaskProgress.SetFloat(_ImageWidget.GetMaskProgress());
	}

	void OnModel_MaskProgress(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_MaskProgress", "" + sender, args.ToStr());
		#endif
		
		_ImageWidget.SetMaskProgress(_MaskProgress.GetFloat());
	}

	void OnView_MaskTransitionWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_MaskTransitionWidth", "" + sender, args.ToStr());
		#endif
		
		_MaskTransitionWidth.SetFloat(_ImageWidget.GetMaskTransitionWidth());
	}

	void OnModel_MaskTransitionWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_MaskTransitionWidth", "" + sender, args.ToStr());
		#endif
		
		_ImageWidget.SetMaskTransitionWidth(_MaskTransitionWidth.GetFloat());
	}
};
