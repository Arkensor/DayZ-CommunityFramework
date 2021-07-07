class CF_ImageWidget : CF_Widget
{
	reference string Index;
	reference string File;
	reference string MaskFile;
	reference string MaskProgress;
	reference string MaskTransitionWidth;

	protected ImageWidget _ImageWidget;
	protected CF_TypeConverter _Index;
	protected CF_TypeConverter _File;
	protected CF_TypeConverter _MaskFile;
	protected CF_TypeConverter _MaskProgress;
	protected CF_TypeConverter _MaskTransitionWidth;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Index, "Index");
		AddProperty(File, "File");
		AddProperty(MaskFile, "MaskFile");
		AddProperty(MaskProgress, "MaskProgress");
		AddProperty(MaskTransitionWidth, "MaskTransitionWidth");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ImageWidget, w);
	}

	void OnView_Index(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Index", "" + model, evt.String());
		
		_Index.SetInt(_ImageWidget.GetImage());
		_Index.ToVariable(model, Index);
	}

	void OnModel_Index(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Index", "" + model, evt.String());
		
		_Index.FromVariable(model, Index);
		_ImageWidget.SetImage(_Index.GetInt());
	}

	void OnView_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_File", "" + model, evt.String());
		
		_File.ToVariable(model, File);
	}

	void OnModel_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_File", "" + model, evt.String());
		
		_File.FromVariable(model, File);
		_ImageWidget.LoadImageFile(_Index.GetInt(), _File.GetString());
	}

	void OnView_MaskFile(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskFile", "" + model, evt.String());
		
		_MaskFile.ToVariable(model, MaskFile);
	}

	void OnModel_MaskFile(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskFile", "" + model, evt.String());
		
		_MaskFile.FromVariable(model, MaskFile);
		_ImageWidget.LoadMaskTexture(_MaskFile.GetString());
	}

	void OnView_MaskProgress(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskProgress", "" + model, evt.String());
		
		_MaskProgress.SetFloat(_ImageWidget.GetMaskProgress());
		_MaskProgress.ToVariable(model, MaskProgress);
	}

	void OnModel_MaskProgress(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskProgress", "" + model, evt.String());
		
		_MaskProgress.FromVariable(model, MaskProgress);
		_ImageWidget.SetMaskProgress(_MaskProgress.GetFloat());
	}

	void OnView_MaskTransitionWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskTransitionWidth", "" + model, evt.String());
		
		_MaskTransitionWidth.SetFloat(_ImageWidget.GetMaskTransitionWidth());
		_MaskTransitionWidth.ToVariable(model, MaskTransitionWidth);
	}

	void OnModel_MaskTransitionWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskTransitionWidth", "" + model, evt.String());
		
		_MaskTransitionWidth.FromVariable(model, MaskTransitionWidth);
		_ImageWidget.SetMaskTransitionWidth(_MaskTransitionWidth.GetFloat());
	}
};
