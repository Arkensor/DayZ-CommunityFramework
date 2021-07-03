class CF_ImageWidget : CF_Widget
{
	reference string Index;
	reference string File;

	reference string MaskFile;
	reference string MaskProgress;
	reference string MaskTransitionWidth;

	protected ImageWidget _ImageWidget;
	protected int _Index;
	protected string _File;
	protected string _MaskFile;

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
		
		int _value = _ImageWidget.GetImage();
		EnScript.SetClassVar(model, Index, 0, _value);
	}

	void OnModel_Index(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Index", "" + model, evt.String());
		
		EnScript.GetClassVar(model, Index, 0, _Index);
		_ImageWidget.SetImage(_Index);
	}

	void OnView_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_File", "" + model, evt.String());
		
		EnScript.SetClassVar(model, File, 0, _File);
	}

	void OnModel_File(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_File", "" + model, evt.String());
		
		EnScript.GetClassVar(model, File, 0, _File);
		_ImageWidget.LoadImageFile(_Index, _File);
	}

	void OnView_MaskFile(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskFile", "" + model, evt.String());
		
		EnScript.SetClassVar(model, MaskFile, 0, _MaskFile);
	}

	void OnModel_MaskFile(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskFile", "" + model, evt.String());
		
		EnScript.GetClassVar(model, MaskFile, 0, _MaskFile);
		_ImageWidget.LoadMaskTexture(_MaskFile);
	}

	void OnView_MaskProgress(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskProgress", "" + model, evt.String());
		
		int _value = _ImageWidget.GetMaskProgress();
		EnScript.SetClassVar(model, MaskProgress, 0, _value);
	}

	void OnModel_MaskProgress(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskProgress", "" + model, evt.String());
		
		float _value;
		EnScript.GetClassVar(model, MaskProgress, 0, _value);
		_ImageWidget.SetMaskProgress(_value);
	}

	void OnView_MaskTransitionWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_MaskTransitionWidth", "" + model, evt.String());
		
		int _value = _ImageWidget.GetMaskTransitionWidth();
		EnScript.SetClassVar(model, MaskTransitionWidth, 0, _value);
	}

	void OnModel_MaskTransitionWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_MaskTransitionWidth", "" + model, evt.String());
		
		float _value;
		EnScript.GetClassVar(model, MaskTransitionWidth, 0, _value);
		_ImageWidget.SetMaskTransitionWidth(_value);
	}
};
