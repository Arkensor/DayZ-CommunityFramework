class CF_ButtonWidget : CF_UIWidget
{
	reference string State;
	reference string Text;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextHorizontalAlignment;
	reference string TextVerticalAlignment;
	reference string TextProportion;

	private ButtonWidget _ButtonWidget;
	private string _Text;
	private float _TextOffsetX;
	private float _TextOffsetY;
	private float _TextHorizontalAlignment;
	private float _TextVerticalAlignment;

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_ButtonWidget, w);
	}
	
	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(State, "State");
		AddProperty(Text, "Text");
	}

	void OnView_State(CF_Model_Base model)
	{
		bool _state = _ButtonWidget.GetState();
		EnScript.SetClassVar(model, State, 0, _state);
	}

	void OnModel_State(CF_Model_Base model)
	{
		bool _state;
		EnScript.GetClassVar(model, State, 0, _state);
		_ButtonWidget.SetState(_state);
	}

	void OnView_Text(CF_Model_Base model)
	{
		CF_MVVM_StringConverter.Set(model, Text, _Text);
	}

	void OnModel_Text(CF_Model_Base model)
	{
		CF_MVVM_StringConverter.Get(model, Text, _Text);
		_ButtonWidget.SetText(_Text);
	}

	void OnView_TextOffsetX(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextOffsetX, 0, _TextOffsetX);
	}

	void OnModel_TextOffsetX(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextOffsetX, 0, _TextOffsetX);
		_ButtonWidget.SetTextOffset(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextOffsetY(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextOffsetY, 0, _TextOffsetY);
	}

	void OnModel_TextOffsetY(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextOffsetY, 0, _TextOffsetY);
		_ButtonWidget.SetTextOffset(_TextOffsetX, _TextOffsetY);
	}

	void OnView_TextHorizontalAlignment(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextHorizontalAlignment, 0, _TextHorizontalAlignment);
	}

	void OnModel_TextHorizontalAlignment(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextHorizontalAlignment, 0, _TextHorizontalAlignment);
		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment);
	}

	void OnView_TextVerticalAlignment(CF_Model_Base model)
	{
		EnScript.SetClassVar(model, TextVerticalAlignment, 0, _TextVerticalAlignment);
	}

	void OnModel_TextVerticalAlignment(CF_Model_Base model)
	{
		EnScript.GetClassVar(model, TextVerticalAlignment, 0, _TextVerticalAlignment);
		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment);
	}

	void OnView_TextProportion(CF_Model_Base model)
	{
		float _TextProportion = _ButtonWidget.GetTextProportion();
		EnScript.SetClassVar(model, TextProportion, 0, _TextProportion);
	}

	void OnModel_TextProportion(CF_Model_Base model)
	{
		float _TextProportion;
		EnScript.GetClassVar(model, TextProportion, 0, _TextProportion);
		_ButtonWidget.SetTextProportion(_TextProportion);
	}
};
