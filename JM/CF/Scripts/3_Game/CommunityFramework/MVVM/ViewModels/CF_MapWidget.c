class CF_MapUserMark : CF_ModelBase
{
	vector Position;
	string Text;
	int Color;
	string TexturePath;
};

class CF_MapWidget : CF_BaseListboxWidget
{
	reference string UserMarks;
	reference string Position;
	reference string Scale;

	protected MapWidget _MapWidget;
	protected CF_ObservableCollection _UserMarks;
	protected CF_MVVM_PropertyBase _Position = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Scale = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetProperties");
		#endif

		super.GetProperties();
		
		AddProperty(UserMarks, "UserMarks");
		AddProperty(Position, "Position");
		AddProperty(Scale, "Scale");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);
		#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MapWidget, w);
	}

	void OnView_UserMarks(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_UserMarks", "" + sender, args.ToStr());
		#endif

		OnModel_UserMarks(sender, args);
	}

	void OnModel_UserMarks(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_UserMarks", "" + sender, args.ToStr());
		#endif

		_MapWidget.ClearUserMarks();
		for (int i = 0; i < _UserMarks.Count(); i++)
		{
			CF_MapUserMark userMark;
			if (!Class.CastTo(userMark, _UserMarks.GetClass(i))) break;

			_MapWidget.AddUserMark(userMark.Position, userMark.Text, userMark.Color, userMark.TexturePath);
		}
	}
	
	void OnView_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Position", "" + sender, args.ToStr());
		#endif

		_Position.SetVector(_MapWidget.GetMapPos());
	}

	void OnModel_Position(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Position", "" + sender, args.ToStr());
		#endif
		
		_MapWidget.SetMapPos(_Position.GetVector());
	}
	
	void OnView_Scale(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView_Scale", "" + sender, args.ToStr());
		#endif
		
		_Scale.SetFloat(_MapWidget.GetScale());
	}

	void OnModel_Scale(CF_ModelBase sender, CF_EventArgs args)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel_Scale", "" + sender, args.ToStr());
		#endif
		
		_MapWidget.SetScale(_Scale.GetFloat());
	}
};
