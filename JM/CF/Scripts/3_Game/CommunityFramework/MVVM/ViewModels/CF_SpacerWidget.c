class CF_SpacerWidget : CF_SpacerBaseWidget
{
	reference string ContentAlignmentHorizontal;
	reference string ContentAlignmentVertical;

	protected SpacerWidget _SpacerWidget;
	protected CF_TypeConverter _ContentAlignmentHorizontal = CF_GetDefaultTC();
	protected CF_TypeConverter _ContentAlignmentVertical = CF_GetDefaultTC();
	
	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();

		AddProperty(ContentAlignmentHorizontal, "ContentAlignmentHorizontal");
		AddProperty(ContentAlignmentVertical, "ContentAlignmentVertical");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerWidget, w);
	}

	void OnView_ContentAlignmentHorizontal(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ContentAlignmentHorizontal", "" + sender, args.ToStr());

		int _contentAlignmentH = _SpacerWidget.GetContentAlignmentH();
		EnScript.SetClassVar(m_Model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
	}

	void OnModel_ContentAlignmentHorizontal(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ContentAlignmentHorizontal", "" + sender, args.ToStr());

		int _contentAlignmentH;
		EnScript.GetClassVar(m_Model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
		_SpacerWidget.SetContentAlignmentH(_contentAlignmentH);
	}

	void OnView_ContentAlignmentVertical(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ContentAlignmentVertical", "" + sender, args.ToStr());

		int _contentAlignmentV = _SpacerWidget.GetContentAlignmentV();
		EnScript.SetClassVar(m_Model, ContentAlignmentVertical, 0, _contentAlignmentV);
	}

	void OnModel_ContentAlignmentVertical(Class sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ContentAlignmentVertical", "" + sender, args.ToStr());

		int _contentAlignmentV;
		EnScript.GetClassVar(m_Model, ContentAlignmentVertical, 0, _contentAlignmentV);
		_SpacerWidget.SetContentAlignmentV(_contentAlignmentV);
	}
};
