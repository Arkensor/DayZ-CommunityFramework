class CF_ButtonWidget : CF_UIWidget
{
	reference string State;
	reference string Text;
	reference string TextOffsetX;
	reference string TextOffsetY;
	reference string TextHorizontalAlignment;
	reference string TextVerticalAlignment;
	reference string TextProportion;

	protected ButtonWidget _ButtonWidget;
	protected CF_MVVM_PropertyBase _State = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Text = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetX = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextOffsetY = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextHorizontalAlignment = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextVerticalAlignment = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _TextProportion = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(State, "State");
		AddProperty(Text, "Text");
		AddProperty(TextOffsetX, "TextOffsetX");
		AddProperty(TextOffsetY, "TextOffsetY");
		AddProperty(TextHorizontalAlignment, "TextHorizontalAlignment");
		AddProperty(TextVerticalAlignment, "TextVerticalAlignment");
		AddProperty(TextProportion, "TextProportion");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_ButtonWidget, w);
	}

	void OnView_State(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_State", "" + sender, args.ToStr());
		#endif

		_State.SetBool(_ButtonWidget.GetState());
	}

	void OnModel_State(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_State", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetState(_State.GetBool());
	}

	void OnView_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Text", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_Text(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Text", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetText(_Text.GetString());
	}

	void OnView_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOffsetX", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_TextOffsetX(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOffsetX", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextOffsetY", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_TextOffsetY(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextOffsetY", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetTextOffset(_TextOffsetX.GetFloat(), _TextOffsetY.GetFloat());
	}

	void OnView_TextHorizontalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextHorizontalAlignment", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_TextHorizontalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextHorizontalAlignment", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetTextHorizontalAlignment(_TextHorizontalAlignment.GetInt());
	}

	void OnView_TextVerticalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextVerticalAlignment", "" + sender, args.ToStr());
		#endif
		
	}

	void OnModel_TextVerticalAlignment(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextVerticalAlignment", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetTextVerticalAlignment(_TextVerticalAlignment.GetInt());
	}

	void OnView_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_TextProportion", "" + sender, args.ToStr());
		#endif
		
		_TextProportion.SetInt(_ButtonWidget.GetTextProportion());
	}

	void OnModel_TextProportion(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_TextProportion", "" + sender, args.ToStr());
		#endif
		
		_ButtonWidget.SetTextProportion(_TextProportion.GetInt());
	}

	override bool OnChange(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnChange", args.ToStr());
		#endif

		if (!args.Continue)
		{
			_ButtonWidget.SetState(false);
		}

		NotifyPropertyChanged(State, "State");

		return true;
	}
};
