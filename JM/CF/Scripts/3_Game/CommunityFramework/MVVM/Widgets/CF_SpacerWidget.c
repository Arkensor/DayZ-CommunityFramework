class CF_SpacerWidget : CF_SpacerBaseWidget
{
	reference string ContentAlignmentHorizontal;
	reference string ContentAlignmentVertical;

	protected SpacerWidget _SpacerWidget;
	protected CF_TypeConverter _ContentAlignmentHorizontal;
	protected CF_TypeConverter _ContentAlignmentVertical;
	
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

	void OnView_ContentAlignmentHorizontal(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentAlignmentHorizontal", "" + model, evt.String());

		int _contentAlignmentH = _SpacerWidget.GetContentAlignmentH();
		EnScript.SetClassVar(model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
	}

	void OnModel_ContentAlignmentHorizontal(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentAlignmentHorizontal", "" + model, evt.String());

		int _contentAlignmentH;
		EnScript.GetClassVar(model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
		_SpacerWidget.SetContentAlignmentH(_contentAlignmentH);
	}

	void OnView_ContentAlignmentVertical(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentAlignmentVertical", "" + model, evt.String());

		int _contentAlignmentV = _SpacerWidget.GetContentAlignmentV();
		EnScript.SetClassVar(model, ContentAlignmentVertical, 0, _contentAlignmentV);
	}

	void OnModel_ContentAlignmentVertical(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentAlignmentVertical", "" + model, evt.String());

		int _contentAlignmentV;
		EnScript.GetClassVar(model, ContentAlignmentVertical, 0, _contentAlignmentV);
		_SpacerWidget.SetContentAlignmentV(_contentAlignmentV);
	}
};
