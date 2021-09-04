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
		auto trace = CF_Trace_0(this, "GetProperties");
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
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ImageWidget, w);
	}

	void OnView_Index(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Index").Add(sender).Add(args.ToStr());
		#endif
		
		_Index.SetInt(_ImageWidget.GetImage());
	}

	void OnModel_Index(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Index").Add(sender).Add(args.ToStr());
		#endif
		
		_ImageWidget.SetImage(_Index.GetInt());
	}

	void OnView_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_File").Add(sender).Add(args.ToStr());
		#endif
		
	}

	void OnModel_File(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_File").Add(sender).Add(args.ToStr());
		#endif
		
		_ImageWidget.LoadImageFile(_Index.GetInt(), _File.GetString());
	}

	void OnView_MaskFile(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_MaskFile").Add(sender).Add(args.ToStr());
		#endif
		
	}

	void OnModel_MaskFile(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_MaskFile").Add(sender).Add(args.ToStr());
		#endif
		
		_ImageWidget.LoadMaskTexture(_MaskFile.GetString());
	}

	void OnView_MaskProgress(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_MaskProgress").Add(sender).Add(args.ToStr());
		#endif
		
		_MaskProgress.SetFloat(_ImageWidget.GetMaskProgress());
	}

	void OnModel_MaskProgress(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_MaskProgress").Add(sender).Add(args.ToStr());
		#endif
		
		_ImageWidget.SetMaskProgress(_MaskProgress.GetFloat());
	}

	void OnView_MaskTransitionWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_MaskTransitionWidth").Add(sender).Add(args.ToStr());
		#endif
		
		_MaskTransitionWidth.SetFloat(_ImageWidget.GetMaskTransitionWidth());
	}

	void OnModel_MaskTransitionWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_MaskTransitionWidth").Add(sender).Add(args.ToStr());
		#endif
		
		_ImageWidget.SetMaskTransitionWidth(_MaskTransitionWidth.GetFloat());
	}
};
