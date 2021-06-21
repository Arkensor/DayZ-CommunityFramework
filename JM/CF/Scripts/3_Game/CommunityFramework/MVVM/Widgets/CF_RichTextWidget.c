class CF_RichTextWidget : CF_TextWidget
{
	reference string ContentHeight;
	reference string ContentOffset;
	reference string ContentSnapToLine;
	reference string LineWidths;

	protected RichTextWidget _RichTextWidget;
	protected bool _ContentSnapToLine;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_RichTextWidget, w);
	}

	void OnView_ContentHeight(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, ContentHeight, 0, _RichTextWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_Model_Base model)
	{
		OnView_ContentHeight(model);
	}

	void OnView_ContentOffset(CF_Model_Base model)
	{
		float _value = _RichTextWidget.GetContentOffset();
		EnScript.SetClassVar(model, ContentOffset, 0, _value);
	}

	void OnModel_ContentOffset(CF_Model_Base model)
	{
		float _value;
		EnScript.GetClassVar(model, ContentOffset, 0, _value);
		_RichTextWidget.SetContentOffset(_value, _ContentSnapToLine);
	}

	void OnView_ContentSnapToLine(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
	}

	void OnModel_ContentSnapToLine(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
		_RichTextWidget.SetContentOffset(_RichTextWidget.GetContentOffset(), _ContentSnapToLine);
	}

	void OnView_LineWidths(CF_Model_Base model)
	{
		array<float> _value;
		EnScript.GetClassVar(model, LineWidths, 0, _value);

		_value.Clear();
		for (int i = 0; i < _RichTextWidget.GetNumLines(); i++)
		{
			_value.Insert(_RichTextWidget.GetLineWidth(i));
		}
	}

	void OnModel_LineWidths(CF_Model_Base model)
	{
		OnView_LineWidths(model);
	}
};
