class CF_CanvasLine : CF_ModelBase
{
	float x1;
	float y1;
	float x2;
	float y2;
	float width;
	int color;
};

class CF_CanvasWidget : CF_Widget
{
	reference string Lines;

	protected CanvasWidget _CanvasWidget;
	protected CF_ObservableCollection _Lines;

	override void GetProperties()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(Lines, "Lines");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_CanvasWidget, w);
	}

	void OnView_Lines(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Lines").Add(sender).Add(args);
#endif
	}

	//! Automatically updated from Collection events so 'NotifyProperty' isn't needed to be called.
	void OnModel_Lines(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Lines").Add(sender).Add(args);
#endif

		_CanvasWidget.Clear();
		for (int i = 0; i < _Lines.Count(); i++)
		{
			CF_CanvasLine line;
			if (!Class.CastTo(line, _Lines.GetClass(i)))
				break;
			_CanvasWidget.DrawLine(line.x1, line.y1, line.x2, line.y2, line.width, line.color);
		}
	}
};
