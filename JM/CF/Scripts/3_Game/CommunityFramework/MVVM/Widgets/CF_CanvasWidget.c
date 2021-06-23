class CF_CanvasLine
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
	protected ref CF_ObservableCollection _Lines;

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(Lines, "Lines");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_CanvasWidget, w);
	}

	void OnView_Lines(CF_Model_Base model, CF_Event evt)
	{
		EnScript.SetClassVar(model, Lines, 0, _Lines);
	}

	void OnModel_Lines(CF_Model_Base model, CF_Event evt)
	{
		EnScript.GetClassVar(model, Lines, 0, _Lines);

		_CanvasWidget.Clear();
		for (int i = 0; i < _Lines.Count(); i++)
		{
			CF_CanvasLine line;
			if (!Class.CastTo(line, _Lines.GetRaw(i))) break;
			_CanvasWidget.DrawLine(line.x1, line.y1, line.x2, line.y2, line.width, line.color);
		}
	}
};
