class CF_SpacerWidget : CF_SpacerBaseWidget
{
	reference string ContentAlignmentHorizontal;
	reference string ContentAlignmentVertical;

	protected SpacerWidget _SpacerWidget;
	
	override void GetProperties()
	{
		super.GetProperties();

		AddProperty(ContentAlignmentHorizontal, "ContentAlignmentHorizontal");
		AddProperty(ContentAlignmentVertical, "ContentAlignmentVertical");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_SpacerWidget, w);
	}

	void OnView_ContentAlignmentHorizontal(CF_Model_Base model)
	{
		int _contentAlignmentH = _SpacerWidget.GetContentAlignmentH();
		EnScript.SetClassVar(model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
	}

	void OnModel_ContentAlignmentHorizontal(CF_Model_Base model)
	{
		int _contentAlignmentH;
		EnScript.GetClassVar(model, ContentAlignmentHorizontal, 0, _contentAlignmentH);
		_SpacerWidget.SetContentAlignmentH(_contentAlignmentH);
	}

	void OnView_ContentAlignmentVertical(CF_Model_Base model)
	{
		int _contentAlignmentV = _SpacerWidget.GetContentAlignmentV();
		EnScript.SetClassVar(model, ContentAlignmentVertical, 0, _contentAlignmentV);
	}

	void OnModel_ContentAlignmentVertical(CF_Model_Base model)
	{
		int _contentAlignmentV;
		EnScript.GetClassVar(model, ContentAlignmentVertical, 0, _contentAlignmentV);
		_SpacerWidget.SetContentAlignmentV(_contentAlignmentV);
	}
};
