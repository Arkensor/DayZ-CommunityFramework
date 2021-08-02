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
	protected ref CF_TypeConverter _ScrollbarWidth = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ContentWidth = CF_GetDefaultTC();
	protected ref CF_TypeConverter _ContentHeight = CF_GetDefaultTC();
	protected ref CF_TypeConverter _HorizontalScrollPosition = CF_GetDefaultTC();
	protected ref CF_TypeConverter _VerticalScrollPosition = CF_GetDefaultTC();
	protected ref CF_TypeConverter _HorizontalScrollStep = CF_GetDefaultTC();
	protected ref CF_TypeConverter _VerticalScrollStep = CF_GetDefaultTC();

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

	void OnView_ScrollbarWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ScrollbarWidth", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, ScrollbarWidth, 0, _ScrollWidget.GetScrollbarWidth());
	}

	void OnModel_ScrollbarWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ScrollbarWidth", "" + sender, args.ToStr());

		OnView_ScrollbarWidth(m_Model, args);
	}

	void OnView_ContentWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ContentWidth", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, ContentWidth, 0, _ScrollWidget.GetContentWidth());
	}

	void OnModel_ContentWidth(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ContentWidth", "" + sender, args.ToStr());

		OnView_ContentWidth(m_Model, args);
	}

	void OnView_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_ContentHeight", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, ContentHeight, 0, _ScrollWidget.GetContentHeight());
	}

	void OnModel_ContentHeight(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_ContentHeight", "" + sender, args.ToStr());

		OnView_ContentHeight(m_Model, args);
	}

	void OnView_HorizontalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_HorizontalScrollPosition", "" + sender, args.ToStr());

		float _value = _ScrollWidget.GetHScrollPos();
		EnScript.SetClassVar(m_Model, HorizontalScrollPosition, 0, _value);
	}

	void OnModel_HorizontalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_HorizontalScrollPosition", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, HorizontalScrollPosition, 0, _value);
		_ScrollWidget.HScrollToPos(_value);
	}

	void OnView_VerticalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_VerticalScrollPosition", "" + sender, args.ToStr());

		float _value = _ScrollWidget.GetVScrollPos();
		EnScript.SetClassVar(m_Model, VerticalScrollPosition, 0, _value);
	}

	void OnModel_VerticalScrollPosition(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_VerticalScrollPosition", "" + sender, args.ToStr());

		float _value;
		EnScript.GetClassVar(m_Model, VerticalScrollPosition, 0, _value);
		_ScrollWidget.VScrollToPos(_value);
	}

	void OnView_HorizontalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_HorizontalScrollStep", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, HorizontalScrollStep, 0, _HorizontalScrollStep);
	}

	void OnModel_HorizontalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_HorizontalScrollStep", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, HorizontalScrollStep, 0, _HorizontalScrollStep);
		//_ScrollWidget.HScrollStep(_HorizontalScrollStep);
	}

	void OnView_VerticalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnView_VerticalScrollStep", "" + sender, args.ToStr());

		EnScript.SetClassVar(m_Model, VerticalScrollStep, 0, _VerticalScrollStep);
	}

	void OnModel_VerticalScrollStep(CF_ModelBase sender, CF_EventArgs args)
	{
		CF_Trace trace(this, "OnModel_VerticalScrollStep", "" + sender, args.ToStr());

		EnScript.GetClassVar(m_Model, VerticalScrollStep, 0, _VerticalScrollStep);
		//_ScrollWidget.VScrollStep(_VerticalScrollStep);
	}
};
