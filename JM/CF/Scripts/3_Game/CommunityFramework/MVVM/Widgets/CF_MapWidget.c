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
	protected ref CF_ObservableCollection _UserMarks;
	protected CF_TypeConverter _Position;
	protected CF_TypeConverter _Scale;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(UserMarks, "UserMarks");
		AddProperty(Position, "Position");
		AddProperty(Scale, "Scale");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_MapWidget, w);
	}

	void OnView_UserMarks(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_UserMarks", "" + model, evt.String());

		EnScript.SetClassVar(model, UserMarks, 0, _UserMarks);
	}

	void OnModel_UserMarks(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_UserMarks", "" + model, evt.String());

		EnScript.GetClassVar(model, UserMarks, 0, _UserMarks);

		_MapWidget.ClearUserMarks();
		for (int i = 0; i < _UserMarks.Count(); i++)
		{
			CF_MapUserMark userMark;
			if (!Class.CastTo(userMark, _UserMarks.GetConverter(i).GetClass())) break;

			_MapWidget.AddUserMark(userMark.Position, userMark.Text, userMark.Color, userMark.TexturePath);
		}
	}
	
	void OnView_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Position", "" + model, evt.String());

		_Position.SetVector(_MapWidget.GetMapPos());
		_Position.ToVariable(model, Position);
	}

	void OnModel_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Position", "" + model, evt.String());
		
		_Position.FromVariable(model, Position);
		_MapWidget.SetMapPos(_Position.GetVector());
	}
	
	void OnView_Scale(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Scale", "" + model, evt.String());
		
		_Scale.SetFloat(_MapWidget.GetScale());
		_Scale.ToVariable(model, Scale);
	}

	void OnModel_Scale(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Scale", "" + model, evt.String());
		
		_Scale.FromVariable(model, Scale);
		_MapWidget.SetScale(_Scale.GetFloat());
	}
};
