class CF_RichTextWidget : CF_TextWidget
{
	reference string ContentHeight;
	reference string ContentOffset;
	reference string ContentSnapToLine;
	reference string LineWidths;

	protected RichTextWidget _RichTextWidget;
	protected CF_TypeConverter _ContentHeight;
	protected CF_TypeConverter _ContentOffset;
	protected CF_TypeConverter _ContentSnapToLine;
	protected CF_TypeConverter _LineWidths;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(ContentHeight, "ContentHeight");
		AddProperty(ContentOffset, "ContentOffset");
		AddProperty(ContentSnapToLine, "ContentSnapToLine");
		AddProperty(LineWidths, "LineWidths");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_RichTextWidget, w);
	}

	void OnView_ContentHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentHeight", "" + model, evt.String());

		EnScript.SetClassVar(model, ContentHeight, 0, _RichTextWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentHeight", "" + model, evt.String());

		OnView_ContentHeight(model, evt);
	}

	void OnView_ContentOffset(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentOffset", "" + model, evt.String());

		float _value = _RichTextWidget.GetContentOffset();
		EnScript.SetClassVar(model, ContentOffset, 0, _value);
	}

	void OnModel_ContentOffset(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentOffset", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, ContentOffset, 0, _value);
		_RichTextWidget.SetContentOffset(_value, _ContentSnapToLine);
	}

	void OnView_ContentSnapToLine(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentSnapToLine", "" + model, evt.String());

		EnScript.SetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
	}

	void OnModel_ContentSnapToLine(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentSnapToLine", "" + model, evt.String());

		EnScript.GetClassVar(model, ContentSnapToLine, 0, _ContentSnapToLine);
		_RichTextWidget.SetContentOffset(_RichTextWidget.GetContentOffset(), _ContentSnapToLine);
	}

	void OnView_LineWidths(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_LineWidths", "" + model, evt.String());

		array<float> _value;
		EnScript.GetClassVar(model, LineWidths, 0, _value);

		_value.Clear();
		for (int i = 0; i < _RichTextWidget.GetNumLines(); i++)
		{
			_value.Insert(_RichTextWidget.GetLineWidth(i));
		}
	}

	void OnModel_LineWidths(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_LineWidths", "" + model, evt.String());

		OnView_LineWidths(model, evt);
	}
};
