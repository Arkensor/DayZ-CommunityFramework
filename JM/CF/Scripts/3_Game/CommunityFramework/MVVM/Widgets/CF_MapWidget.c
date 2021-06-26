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

	override void GetProperties()
	{
		super.GetProperties();
		
		AddProperty(UserMarks, "UserMarks");
		AddProperty(Position, "Position");
		AddProperty(Scale, "Scale");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);
		Class.CastTo(_MapWidget, w);
	}

	void OnView_UserMarks(CF_ModelBase model, CF_Event evt)
	{
		EnScript.SetClassVar(model, UserMarks, 0, _UserMarks);
	}

	void OnModel_UserMarks(CF_ModelBase model, CF_Event evt)
	{
		EnScript.GetClassVar(model, UserMarks, 0, _UserMarks);

		_MapWidget.ClearUserMarks();
		for (int i = 0; i < _UserMarks.Count(); i++)
		{
			CF_MapUserMark userMark;
			if (!Class.CastTo(userMark, _UserMarks.GetConverter(i).GetClass())) break;

			_MapWidget.AddUserMark(userMark.Position, userMark.Text, userMark.Color, userMark.TexturePath);
		}
	}
	
	void OnView_Position(CF_ModelBase model, CF_Event evt)
	{
		vector _value = _MapWidget.GetMapPos();
		EnScript.SetClassVar(model, Position, 0, _value);
	}

	void OnModel_Position(CF_ModelBase model, CF_Event evt)
	{
		vector _value;
		EnScript.GetClassVar(model, Position, 0, _value);
		_MapWidget.SetMapPos(_value);
	}
	
	void OnView_Scale(CF_ModelBase model, CF_Event evt)
	{
		float _value = _MapWidget.GetScale();
		EnScript.SetClassVar(model, Scale, 0, _value);
	}

	void OnModel_Scale(CF_ModelBase model, CF_Event evt)
	{
		float _value;
		EnScript.GetClassVar(model, Scale, 0, _value);
		_MapWidget.SetScale(_value);
	}
};
