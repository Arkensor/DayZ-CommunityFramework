class CF_ScrollWidget : CF_SpacerBaseWidget
{
	reference string ScrollbarWidth;
	reference string ContentWidth;
	reference string ContentHeight;
	reference string HorizontalScrollPosition;
	reference string VerticalScrollPosition;
	reference string HorizontalScrollStep;
	reference string VerticalScrollStep;

	protected ScrollWidget _ScrollWidget;
	protected CF_TypeConverter _ScrollbarWidth;
	protected CF_TypeConverter _ContentWidth;
	protected CF_TypeConverter _ContentHeight;
	protected CF_TypeConverter _HorizontalScrollPosition;
	protected CF_TypeConverter _VerticalScrollPosition;
	protected CF_TypeConverter _HorizontalScrollStep;
	protected CF_TypeConverter _VerticalScrollStep;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(ScrollbarWidth, "ScrollbarWidth");
		AddProperty(ContentWidth, "ContentWidth");
		AddProperty(ContentHeight, "ContentHeight");
		AddProperty(HorizontalScrollPosition, "HorizontalScrollPosition");
		AddProperty(VerticalScrollPosition, "VerticalScrollPosition");
		AddProperty(HorizontalScrollStep, "HorizontalScrollStep");
		AddProperty(VerticalScrollStep, "VerticalScrollStep");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ScrollWidget, w);
	}

	void OnView_ScrollbarWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ScrollbarWidth", "" + model, evt.String());

		EnScript.SetClassVar(model, ScrollbarWidth, 0, _ScrollWidget.GetScrollbarWidth());
	}

	void OnModel_ScrollbarWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ScrollbarWidth", "" + model, evt.String());

		OnView_ScrollbarWidth(model, evt);
	}

	void OnView_ContentWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentWidth", "" + model, evt.String());

		EnScript.SetClassVar(model, ContentWidth, 0, _ScrollWidget.GetContentWidth());
	}

	void OnModel_ContentWidth(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentWidth", "" + model, evt.String());

		OnView_ContentWidth(model, evt);
	}

	void OnView_ContentHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_ContentHeight", "" + model, evt.String());

		EnScript.SetClassVar(model, ContentHeight, 0, _ScrollWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_ContentHeight", "" + model, evt.String());

		OnView_ContentHeight(model, evt);
	}

	void OnView_HorizontalScrollPosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_HorizontalScrollPosition", "" + model, evt.String());

		float _value = _ScrollWidget.GetHScrollPos();
		EnScript.SetClassVar(model, HorizontalScrollPosition, 0, _value);
	}

	void OnModel_HorizontalScrollPosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_HorizontalScrollPosition", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, HorizontalScrollPosition, 0, _value);
		_ScrollWidget.HScrollToPos(_value);
	}

	void OnView_VerticalScrollPosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_VerticalScrollPosition", "" + model, evt.String());

		float _value = _ScrollWidget.GetVScrollPos();
		EnScript.SetClassVar(model, VerticalScrollPosition, 0, _value);
	}

	void OnModel_VerticalScrollPosition(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_VerticalScrollPosition", "" + model, evt.String());

		float _value;
		EnScript.GetClassVar(model, VerticalScrollPosition, 0, _value);
		_ScrollWidget.VScrollToPos(_value);
	}

	void OnView_HorizontalScrollStep(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_HorizontalScrollStep", "" + model, evt.String());

		EnScript.SetClassVar(model, HorizontalScrollStep, 0, _HorizontalScrollStep);
	}

	void OnModel_HorizontalScrollStep(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_HorizontalScrollStep", "" + model, evt.String());

		EnScript.GetClassVar(model, HorizontalScrollStep, 0, _HorizontalScrollStep);
		_ScrollWidget.HScrollStep(_HorizontalScrollStep);
	}

	void OnView_VerticalScrollStep(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_VerticalScrollStep", "" + model, evt.String());

		EnScript.SetClassVar(model, VerticalScrollStep, 0, _VerticalScrollStep);
	}

	void OnModel_VerticalScrollStep(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_VerticalScrollStep", "" + model, evt.String());

		EnScript.GetClassVar(model, VerticalScrollStep, 0, _VerticalScrollStep);
		_ScrollWidget.VScrollStep(_VerticalScrollStep);
	}
};
