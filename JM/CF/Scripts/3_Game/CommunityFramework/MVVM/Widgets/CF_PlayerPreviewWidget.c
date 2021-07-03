class CF_PlayerPreviewWidget : CF_Widget
{
	reference string Player;
	reference string HandItem;
	reference string Orientation;
	reference string Position;

	protected PlayerPreviewWidget _PlayerPreviewWidget;
	protected EntityAI _HandItem;

	override void GetProperties()
	{
		CF_Trace trace(this, "GetProperties");

		super.GetProperties();
		
		AddProperty(Player, "Player");
		AddProperty(HandItem, "HandItem");
		AddProperty(Orientation, "Orientation");
		AddProperty(Position, "Position");
	}

	override void OnWidgetScriptInit(Widget w)
	{
		CF_Trace trace(this, "OnWidgetScriptInit", "" + w);

		super.OnWidgetScriptInit(w);
		Class.CastTo(_PlayerPreviewWidget, w);
	}

	void OnView_Player(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Player", "" + model, evt.String());

		DayZPlayer _value = _PlayerPreviewWidget.GetDummyPlayer();
		EnScript.SetClassVar(model, Player, 0, _value);
	}

	void OnModel_Player(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Player", "" + model, evt.String());

		DayZPlayer _value;
		EnScript.GetClassVar(model, Player, 0, _value);
		_PlayerPreviewWidget.SetPlayer(_value);
	}

	void OnView_HandItem(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_HandItem", "" + model, evt.String());

		EnScript.SetClassVar(model, HandItem, 0, _HandItem);
	}

	void OnModel_HandItem(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_HandItem", "" + model, evt.String());

		EnScript.GetClassVar(model, HandItem, 0, _HandItem);
		_PlayerPreviewWidget.UpdateItemInHands(_HandItem);
	}

	void OnView_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Orientation", "" + model, evt.String());

		vector _value = _PlayerPreviewWidget.GetModelOrientation();
		EnScript.SetClassVar(model, Orientation, 0, _value);
	}

	void OnModel_Orientation(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Orientation", "" + model, evt.String());

		vector _value;
		EnScript.GetClassVar(model, Orientation, 0, _value);
		_PlayerPreviewWidget.SetModelOrientation(_value);
	}

	void OnView_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView_Position", "" + model, evt.String());

		vector _value = _PlayerPreviewWidget.GetModelPosition();
		EnScript.SetClassVar(model, Position, 0, _value);
	}

	void OnModel_Position(CF_ModelBase model, CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel_Position", "" + model, evt.String());

		vector _value;
		EnScript.GetClassVar(model, Position, 0, _value);
		_PlayerPreviewWidget.SetModelPosition(_value);
	}
};
