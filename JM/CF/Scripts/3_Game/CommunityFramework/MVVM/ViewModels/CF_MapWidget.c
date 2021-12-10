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
	reference string CenterPosition;
	reference string Scale;

	protected MapWidget _MapWidget;
	protected CF_ObservableCollection _UserMarks;
	protected CF_MVVM_PropertyBase _CenterPosition = CF_MVVM_GetDefaultProperty();
	protected CF_MVVM_PropertyBase _Scale = CF_MVVM_GetDefaultProperty();

	override void GetProperties()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "GetProperties");
#endif

		super.GetProperties();

		AddProperty(UserMarks, "UserMarks");
		AddProperty(CenterPosition, "CenterPosition");
		AddProperty(Scale, "Scale");
	}

	override void OnWidgetScriptInit(Widget w)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnWidgetScriptInit").Add(w);
#endif

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MapWidget, w);
	}

	void OnView_UserMarks(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_UserMarks").Add(sender).Add(args);
#endif

		OnModel_UserMarks(sender, args);
	}

	void OnModel_UserMarks(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_UserMarks").Add(sender).Add(args);
#endif

		_MapWidget.ClearUserMarks();
		for (int i = 0; i < _UserMarks.Count(); i++)
		{
			CF_MapUserMark userMark;
			if (!Class.CastTo(userMark, _UserMarks.GetClass(i)))
				break;

			_MapWidget.AddUserMark(userMark.Position, userMark.Text, userMark.Color, userMark.TexturePath);
		}
	}

	void OnView_CenterPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_CenterPosition").Add(sender).Add(args);
#endif

		_CenterPosition.SetVector(_MapWidget.GetMapPos());
	}

	void OnModel_CenterPosition(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_CenterPosition").Add(sender).Add(args);
#endif

		_MapWidget.SetMapPos(_CenterPosition.GetVector());
	}

	void OnView_Scale(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnView_Scale").Add(sender).Add(args);
#endif

		_Scale.SetFloat(_MapWidget.GetScale());
	}

	void OnModel_Scale(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "OnModel_Scale").Add(sender).Add(args);
#endif

		_MapWidget.SetScale(_Scale.GetFloat());
	}
};
